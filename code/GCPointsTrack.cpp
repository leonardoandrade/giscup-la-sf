#include "GCPointsTrack.h"
#include "geos/geom/LineString.h"
#include "geos/geom/Coordinate.h"
#include "geos/geom/CoordinateSequence.h"
#include "geos/geom/Point.h"
#include "geos/geom/GeometryFactory.h"
#include "geos/geom/PrecisionModel.h"
#include <math.h>
#include <string.h>
#include <sstream>

using namespace std;

float distance(float x0, float y0, float x1, float y1)
{
    return sqrt(pow(x1-x0,2)+pow(y1-y0,2));
}

GCPointsTrack::GCPointsTrack()
{
    points=new vector<GCPoint*>();
}

GCPointsTrack::~GCPointsTrack()
{
    for(int i =0; i<points->size(); i++)
    {
        GCPoint * p = points->at(i);
        delete p;
    }
    delete points;
}

void GCPointsTrack::setEvalParams(GCEvalParams * ep)
{
    eval_params=ep;
}

int GCPointsTrack::numberPoints()
{
    return points->size();
}

void GCPointsTrack::addPoint(int id, double x, double y, int edge)
{
    GCPoint * p = new GCPoint(id, x, y);
    p->edge=edge;
    points->push_back(p);
}

GCPoint * GCPointsTrack::getPointAt(int idx)
{
    return (points->at(idx));
}

struct edge_distance
{
    float distance;
    GCEdge * edge;
};

bool comp_edge_distance(edge_distance e1, edge_distance e2)
{
    return e1.distance<e2.distance;
}

/*class*/
void GCPointsTrack::findNearestEdges(GCRoadNetwork * rn)
{


    //cout << "processing track with  " << points->size() << " points" << endl;
    for(int i=0; i<points->size(); i++)
    {
        //cout << "processing point "<< i << "/" << points->size() << endl;
        GCPoint * p = (points->at(i));
        //int n_edges=rn->numberEdges();
        //int closest_edge_id=-99;
        //float closest_edge_distance=9999999999.0;
        vector <GCEdge*> ee = rn->findEdgesByRadius(p,300);



        //sort the vector

        vector <edge_distance> eedd;
        GeometryFactory factory;
        Point * pp =factory.createPoint(Coordinate(p->x, p->y));

        for(int j = 0; j < ee.size(); j++)
        {
            GCEdge * e = ee[j];
            LineString * ls=e->getGeometry();
            float dist=ls->distance(pp);
            edge_distance ed;
            ed.distance=dist;
            ed.edge=e;
            eedd.push_back(ed);
        }
        sort(eedd.begin(), eedd.end(), comp_edge_distance);
        p->num_edges=min((int)EVALUATED_EDGES, (int)eedd.size());
        for(int i=0; i < p->num_edges; i++)
        {

            p->edges_distances[i]=1.0/(eedd[i].distance+1.0);
            p->edges_ids[i]=eedd[i].edge->getId();
            p->edges[i]=eedd[i].edge;
        }


        /*
        for(int i=0; i < p->num_edges; i++)
        {
            cout << "#" << i << ": " << p->id << ":" << p->edges[i]->getId()  <<  ", "<<  p->edges_distances[i] << endl;

        }
        */
        delete pp;
    }
}


void GCPointsTrack::weightDirection(GCRoadNetwork * rn)
{

    //computing the direction of the point sequence
    for(int i=1; i<points->size()-1; i++)
    {
        Coordinate c_before =  Coordinate(points->at(i-1)->x,points->at(i-1)->y);
        GCPoint * p = points->at(i);
        Coordinate c_after = Coordinate(points->at(i+1)->x,points->at(i+1)->y);
        //cout << p->id << endl;
        for(int j=0;j<p->num_edges; j++)
        {
            //cout << "\t" << p->edges[j]->getId() << endl;
            Coordinate edge_start_point=p->edges[j]->getStartPoint();
            Coordinate edge_end_point=p->edges[j]->getEndPoint();

            p->edges_direction_weight[j]=(c_after.distance(edge_start_point)-c_before.distance(edge_start_point)-c_after.distance(edge_end_point)-c_before.distance(edge_end_point))/p->edges[j]->getLength();
        }
    }

}

/*second version of the algoritm: weight direction by interception */

void GCPointsTrack::weightDirection2(GCRoadNetwork * rn)
{
    float radius=300.0;
    for(int i=1; i<points->size()-1; i++)
    {

        Coordinate c_before =  Coordinate(points->at(i-1)->x,points->at(i-1)->y);
        GCPoint * p = points->at(i);
        Coordinate c_after = Coordinate(points->at(i+1)->x,points->at(i+1)->y);

        //create the polygon for intersections
        CoordinateArraySequence  * pol_seq=new CoordinateArraySequence();
        pol_seq->add(Coordinate((p->x)-radius, (p->y)-radius));
        pol_seq->add(Coordinate((p->x)-radius, (p->y)+radius));
        pol_seq->add(Coordinate((p->x)+radius, (p->y)+radius));
        pol_seq->add(Coordinate((p->x)+radius, (p->y)-radius));
        pol_seq->add(Coordinate((p->x)-radius, (p->y)-radius));
        GeometryFactory factory;
        Polygon * pol=factory.createPolygon(factory.createLinearRing(pol_seq), NULL);

        std::ostringstream tmp;
        for(int j=0;j < p->num_edges; j++)
        {
            //p->edges[j]->dump();
            //cout << "area:"<< pol->getArea() << endl;

            LineString * ls=factory.createLineString( p->edges[j]->getCoordinateSequence());
            //without the next line, gives segmentation fault....
            tmp << "PM LS:" << ls->getPrecisionModel()->toString() << "PM Pol:" << pol->getPrecisionModel()->toString() << endl;
            Geometry * g = pol->intersection(ls);



            //cout << "type:" << g->getGeometryType() << " length:" <<  g->getLength() << endl;

            //p->edges_direction_weight[j]=(rand()%10)-5;
            if(g->getLength()!=0)
            {
                Coordinate edge_start_point=g->getCoordinates()->front();
                Coordinate edge_end_point=g->getCoordinates()->back();

                p->edges_direction_weight[j]=(c_after.distance(edge_start_point)-c_before.distance(edge_start_point)-c_after.distance(edge_end_point)-c_before.distance(edge_end_point))/p->edges[j]->getLength();
            }
            else
            {
                p->edges_direction_weight[j]=0;
            }
        }
    }
}
/* third version of the algorithm: check the direction of the next and before points*/
void GCPointsTrack::weightDirection3(GCRoadNetwork * rn)
{
        for(int i=1; i<points->size()-1; i++)
        {
            Coordinate c_before =  Coordinate(points->at(i-1)->x,points->at(i-1)->y);
            Coordinate c_middle = Coordinate(points->at(i)->x,points->at(i)->y);
            Coordinate c_after = Coordinate(points->at(i+1)->x,points->at(i+1)->y);
            GCPoint * p = points->at(i);
            for(int j=0;j < p->num_edges; j++)
            {
                CoordinateSequence * seq = p->edges[j]->getCoordinateSequence();
                float c_before_min_dist=999999;
                float c_after_min_dist=999999;
                int c_before_index=-1;
                int c_after_index=-1;

                for(int k=0; k<seq->getSize(); k++)
                {

                    float d_before=c_before.distance(seq->getAt(k));
                    if(d_before < c_before_min_dist)
                    {
                        c_before_min_dist= d_before;
                        c_before_index=k;
                    }
                    float d_after=c_after.distance(seq->getAt(k));
                    if(d_after < c_after_min_dist)
                    {
                        c_after_min_dist= d_after;
                        c_after_index=k;
                    }
                }

                float sim;
                if(c_before_index<c_after_index)
                {
                    sim=1.0;
                }
                else if((c_before_index==c_after_index))
                {
                    float delta_start=c_after.distance(seq->getAt(0)) - c_before.distance(seq->getAt(0));
                    float delta_end=c_after.distance(seq->getAt(seq->size()-1)) - c_before.distance(seq->getAt(seq->size()-1));

                    if(delta_start > delta_end)
                    {

                        sim=1.0;
                    }
                    else
                    {
                        sim=0.0;
                    }
                }
                else
                {
                    sim=0.0;
                }


                GeometryFactory factory;
                Point * p1=factory.createPoint(c_before);
                float d1=p->edges[j]->getGeometry()->distance(p1);
                Point * p2=factory.createPoint(c_middle);
                float d2=p->edges[j]->getGeometry()->distance(p2);
                Point * p3=factory.createPoint(c_after);
                float d3=p->edges[j]->getGeometry()->distance(p3);


                delete p1;
                delete p2;
                delete p3;

                sim=sim*(min(min(d1,d2),d3)/((d1+d2+d3)/3.0));


                //cout << i <<" sim="<<sim<< ";c_before_index=" << c_before_index << ";c_after_index=" << c_after_index\
                 << ";c_before_min_dist=" << c_before_min_dist << ";c_after_min_dist=" << c_after_min_dist << endl;
                p->edges_direction_weight[j]=sim;
            }
        }
}

void GCPointsTrack::computeSpeed()
{
        for(int i=1; i<points->size()-1; i++)
        {
            float dist=distance(points->at(i-1)->x,points->at(i-1)->y,points->at(i+1)->x,points->at(i+1)->y);
            int delta_t=(points->at(i+1)->id)-(points->at(i-1)->id);
            points->at(i)->speed=(dist/(float)delta_t)*3.6;
        }
}





void GCPointsTrack::smoothSimilarity(GCRoadNetwork * rn, int iterations)
{
    this->computeSimilarity(rn);
    for(int x=0; x<iterations;x++)
    {
        for(int i=2; i<points->size()-2; i++)
        {
            GCPoint * p_before_2 = points->at(i-2);
            GCPoint * p_before = points->at(i-1);
            GCPoint * p = points->at(i);
            GCPoint * p_after = points->at(i+1);
            GCPoint * p_after_2 = points->at(i+2);


            for(int j=0;j < p->num_edges; j++)
            {

                /*
                if(p->edges_ids[j]==p_before->edge)
                {
                    p->edges_adjacency_weight[j]=1.0;
                }

                else if((p->edges_ids[j]!=p_before->edge) && (p->edges[j]->startnode==(p_before->best_edge->endnode)))
                {
                     p->edges_adjacency_weight[j]=1.0;
                }
                else if((p->edges_ids[j]!=p_before->edge) && (p->edges[j]->startnode!=(p_before->best_edge->endnode)))
                {
                    p->edges_adjacency_weight[j]=0.0;
                }
                */




                if(p->edges_ids[j]==p_before->edge)
                {
                    p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+eval_params->topology_adjacent_same_edge;
                }
                if(p->edges_ids[j]==p_after->edge)
                {
                    p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+eval_params->topology_adjacent_same_edge;
                }

                if(p->edges_ids[j]==p_before_2->edge)
                {
                    p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+eval_params->topology_adjacent_same_edge;
                }
                if(p->edges_ids[j]==p_after_2->edge)
                {
                    p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+eval_params->topology_adjacent_same_edge;
                }




                if((p->edges_ids[j]!=p_before->edge) && (p->edges[j]->startnode==(p_before->best_edge->endnode)))
                {
                     p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+eval_params->topology_adjacent_accessible;
                }

                if((p->edges_ids[j]!=p_after->edge) && (p->edges[j]->endnode==(p_after->best_edge->startnode)))
                {
                     p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+eval_params->topology_adjacent_accessible;
                }


                /*
                if(strcmp(p->edges[j]->getName().c_str(), p_before->best_edge->getName().c_str())==0)
                {
                    p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+tmp_adj*eval_params->topology_adjacent_same_streetname;
                }
                if(strcmp(p->edges[j]->getName().c_str(), p_after->best_edge->getName().c_str())==0)
                {
                    p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]+tmp_adj*eval_params->topology_adjacent_same_streetname;
                }
                */


                /*normalizing by maximum possible*/
                /*
                p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]/\
                pow(((eval_params->topology_adjacent_same_edge*eval_params->topology_adjacent_accessible*eval_params->topology_adjacent_same_streetname)),2);
                */


            }
            /*normalizing by maximum value*/
            float max_val=0.0;
            for(int j=0;j < p->num_edges; j++)
            {
                if(p->edges_adjacency_weight[j]>max_val)
                {
                    max_val=p->edges_adjacency_weight[j];
                }
            }

            for(int j=0;j < p->num_edges; j++)
            {
               p->edges_adjacency_weight[j]=p->edges_adjacency_weight[j]/max_val;
            }

        }


        this->computeSimilarity(rn);
    }
}
void GCPointsTrack::normalizeValues()
{
    for(int i=0; i<points->size(); i++)
    {
        GCPoint * p = points->at(i);
        float max_dist=0.01; //the problem of division by zero
        float max_direction=0.01;



        for(int j=0;j < p->num_edges; j++)
        {

            p->edges_distances[j]=p->edges_distances[j]*p->edges_distances[j]; // squaring the distance
            if(p->edges_distances[j]>max_dist)
            {
                max_dist=p->edges_distances[j];
            }
            if(p->edges_direction_weight[j]>max_direction)
            {
                max_direction=p->edges_direction_weight[j];
            }

        }
        for(int j=0;j < p->num_edges; j++)
        {
            p->edges_distances[j]=p->edges_distances[j]/max_dist;
            p->edges_direction_weight[j]=p->edges_direction_weight[j]/max_direction;
        }
    }
}

void GCPointsTrack::computeSimilarity(GCRoadNetwork * rn)
{
    //
    //cout << "number points:" <<  points->size() << endl;
    for(int i=0; i<points->size(); i++)
    {

        GCPoint * p = points->at(i);
        for(int j=0;j < p->num_edges; j++)
        {
            p->edges_similarity[j]=(((p->edges_distances[j]) * eval_params->b_distance)+\
                                    ((p->edges_direction_weight[j])  * eval_params->b_direction)+\
                                    ((p->edges_adjacency_weight[j])  * eval_params->b_adjacency));
/*
            p->edges_similarity[j]=((p->edges_distances[j]) / eval_params->b_distance)*\
                                    ((p->edges_direction_weight[j])  / eval_params->b_direction)*\
                                    ((p->edges_adjacency_weight[j])  / eval_params->b_adjacency));
*/

            //cout << "sim:" <<  p->edges_similarity[j] << "eval params: " << eval_params->toStr() << endl;

            //p->edges_similarity[j]=((1.0/p->edges_distances[j])*p->edges_direction_weight[j]*p->edges_adjacency_weight[j]);
            //cout << "sim:" <<  p->edges_similarity[j] << endl;
            p->confidence=1.0;
        }

    }
        for(int i=0; i<points->size(); i++)
        {
            float best=-999999;
            //cout << "num_edges:" << points->at(i)->num_edges << endl;
            for(int j=0;j < points->at(i)->num_edges; j++)
            {
                //cout << "sim2:" << points->at(i)->edges_similarity[j] << "best:" << best << endl;
                if(points->at(i)->edges_similarity[j]>best)
                {
                    best=points->at(i)->edges_similarity[j];
                    points->at(i)->edge = (points->at(i))->edges_ids[j];
                    points->at(i)->best_edge=(points->at(i))->edges[j];
                }

            }
            (points->at(i))->confidence=1.0;
        }
}
