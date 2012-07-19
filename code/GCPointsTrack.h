#include "GC.h"

#ifndef GCPOINTSTRACK_H
#define GCPOINTSTRACK_H

class GCPointsTrack
{
    public:
        GCPointsTrack();
        ~GCPointsTrack();
        void addPoint(int id, double x, double y, int edge);
        void findNearestEdges(GCRoadNetwork * rn);
        void wheightDirection(GCRoadNetwork * rn);
        void wheightDirection2(GCRoadNetwork * rn);
        void wheightDirection3(GCRoadNetwork * rn);
        void wheightAdjacency(GCRoadNetwork * rn);
        void smoothSimilarity(GCRoadNetwork * rn, int iterations);
        void computeSimilarity(GCRoadNetwork * rn);
        void computeSpeed();
        int  numberPoints();
        GCPoint * getPointAt(int idx);

    private:
        vector <GCPoint*> * points;
};

#endif
