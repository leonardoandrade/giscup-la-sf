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

/*simple distance, non-wheighed, confidence allways 1*/
void GCPointsTrack::classifyBySimpleDistance(GCRoadNetwork * rn)
{

    cout << "processing track with  " << points->size() << " points" << endl;
    for(int i=0; i<points->size(); i++)
    {
        cout << "processing point "<< i << "/" << points->size() << endl;
        GCPoint * p = (points->at(i));
        int n_edges=rn->numberEdges();
        int closest_edge_id=-99;
        float closest_edge_distance=9999999999.0;
        vector <GCEdge*> ee = rn->findEdgesByRadius(p,1000);

        GeometryFactory factory;
        for(int j = 0; j < ee.size(); j++)
        {

            GCEdge * e = ee[j];
            LineString * ls=e->getGeometry();

            Point * pp =factory.createPoint(Coordinate(p->x, p->y));
            float dist=ls->distance(pp);
            if(dist < closest_edge_distance)
            {
                closest_edge_distance=dist;
                closest_edge_id=e->getId();
            }
            delete pp;
        }
        p->edge=closest_edge_id;
        p->confidence=1.0;
    }
}


void GCPointsTrack::classifyByWheightedDistance(GCRoadNetwork * rn)
{
    //TODO
}

