#include "GC.h"

#ifndef GCPOINTSTRACK_H
#define GCPOINTSTRACK_H

class GCPointsTrack
{
    public:
       GCPointsTrack();
        ~GCPointsTrack();
       void addPoint(int id, double x, double y, int edge);
       void classifyBySimpleDistance(GCRoadNetwork * rn);
       void classifyByWheightedDistance(GCRoadNetwork * rn);
       int numberPoints();
       GCPoint * getPointAt(int idx);

    private:
        vector <GCPoint*> * points;
};

#endif
