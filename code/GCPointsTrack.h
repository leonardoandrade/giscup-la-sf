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
        void wheightAdjacency(GCRoadNetwork * rn);
        void computeSimilarity(GCRoadNetwork * rn);
        int  numberPoints();
        GCPoint * getPointAt(int idx);

    private:
        vector <GCPoint*> * points;
};

#endif
