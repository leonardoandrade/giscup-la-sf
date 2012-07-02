#include "GC.h"

#ifndef GCPOINTSTRACK_H
#define GCPOINTSTRACK_H

class GCPointsTrack
{
    public:
       GCPointsTrack();
        ~GCPointsTrack();
       void addPoint(int id, float x, float y, int edge);
       void classifyBySimpleDistance(GCRoadNetwork * rn);
       void classifyByWheightedDistance(GCRoadNetwork * rn);
    private:
        vector <GCPoint*> * points;
};

#endif
