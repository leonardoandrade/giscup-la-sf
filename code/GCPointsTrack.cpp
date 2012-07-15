#include "GCPointsTrack.h"
#include "geos/geom/LineString.h"
#include "geos/geom/Coordinate.h"
#include "geos/geom/Point.h"
#include "geos/geom/GeometryFactory.h"


using namespace std;

GCPointsTrack::GCPointsTrack()
{
    points=new vector<GCPoint*>();
}

GCPointsTrack::~GCPointsTrack()
{
    delete points;
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


    cout << "processing track with  " << points->size() << " points" << endl;
    for(int i=0; i<points->size(); i++)
    {
        cout << "processing point "<< i << "/" << points->size() << endl;
        GCPoint * p = (points->at(i));
        //int n_edges=rn->numberEdges();
        //int closest_edge_id=-99;
        //float closest_edge_distance=9999999999.0;
        vector <GCEdge*> ee = rn->findEdgesByRadius(p,10000);



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
        for(int i=0; i<min((int)EVALUATED_EDGES, (int)eedd.size()); i++)
        {

            p->edges_distances[i]=eedd[i].distance;
            p->edges_ids[i]=eedd[i].edge->getId();
            p->edges[i]=eedd[i].edge;
        }
        for(int i=0; i<min((int)EVALUATED_EDGES, (int)eedd.size()); i++)
        {
            cout << "#" << i << ": " << p->id << ":" << p->edges[i]->getId()  <<  ", "<<  p->edges_distances[i] << endl;

        }
        delete pp;
    }
}


void GCPointsTrack::wheightDirection(GCRoadNetwork * rn)
{
    //getting the distances
    /*
    for(int i=0; i<points->size(); i++)
    {
        GCPoint * p = points->at(i);
        for(int j=0;j<EVALUATED_EDGES; j++)
        {
            p->edges_distance_to_start_point[j]= p->edges[i]->getStartPoint().distance(Coordinate(p->x, p->y));
            p->edges_distance_to_end_point[j]= p->edges[i]->getEndPoint().distance(Coordinate(p->x, p->y));
        }
    }
    */
    //computing the direction of the point sequence
    for(int i=1; i<points->size()-1; i++)
    {
        Coordinate c_before =  Coordinate(points->at(i-1)->x,points->at(i-1)->y);
        GCPoint * p = points->at(i);
        Coordinate c_after = Coordinate(points->at(i+1)->x,points->at(i+1)->y);
        cout << p->id << endl;
        for(int j=0;j<EVALUATED_EDGES; j++)
        {
            cout << "\t" << p->edges[j]->getId() << endl;
            Coordinate edge_start_point=p->edges[j]->getStartPoint();
            Coordinate edge_end_point=p->edges[j]->getEndPoint();
            p->edges_distance_to_start_point[j]=c_after.distance(edge_start_point)-c_before.distance(edge_start_point);
            p->edges_distance_to_end_point[j]=c_after.distance(edge_end_point)-c_before.distance(edge_end_point);
            p->edges_direction_wheight[j]=(p->edges_distance_to_start_point[j]-p->edges_distance_to_end_point[j])/p->edges[j]->getLength();
        }
    }
    for(int i=1; i<points->size()-1; i++)
    {
        GCPoint * p = points->at(i);
        for(int j=0;j<EVALUATED_EDGES; j++)
        {
            if(p->edges_direction_wheight[j]>0.0)
            {
                 p->edges_similarity[j]=p->edges_distances[j];
            }
            else
            {
                p->edges_similarity[j]=p->edges_distances[j]*2;
            }
        }
    }


}

void GCPointsTrack::wheightAdjacency(GCRoadNetwork * rn)
{
    //TODO
}

void GCPointsTrack::computeSimilarity(GCRoadNetwork * rn)
{


        for(int i=0; i<points->size(); i++)
        {

            float best=999999;
            for(int j=0;j<EVALUATED_EDGES; j++)
            {
                if(points->at(i)->edges_similarity[j]<best)
                {
                    best=points->at(i)->edges_similarity[j];
                    points->at(i)->edge= (points->at(i))->edges_ids[j];
                }

            }
            points->at(i)->confidence=1.0;
        }
}
