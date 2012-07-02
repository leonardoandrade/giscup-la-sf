#include "GCPointsTrack.h"
using namespace std;

GCPointsTrack::GCPointsTrack()
{
    points=new vector<GCPoint*>();
}


GCPointsTrack::~GCPointsTrack()
{
    delete points;
}

void GCPointsTrack::addPoint(int id, float x, float y, int edge)
{
    GCPoint * p = new GCPoint(id, x, y);
    p->edge=edge;
    points->push_back(p);
}

void GCPointsTrack::classifyBySimpleDistance(GCRoadNetwork * rn)
{
    for(int i=0; i<points->size(); i++)
    {
        (points->at(i))->edge=99;
    }
}


void GCPointsTrack::classifyByWheightedDistance(GCRoadNetwork * rn)
{
    //TODO
}

