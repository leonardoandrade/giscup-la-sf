#include "GC.h"

#ifndef GCPOINTSTRACK_H
#define GCPOINTSTRACK_H
#include "GCEvalParams.h"
class GCPointsTrack
{
    public:
        GCPointsTrack();
        ~GCPointsTrack();
        void addPoint(int id, double x, double y, int edge);
        void findNearestEdges(GCRoadNetwork * rn);
        void weightDirection(GCRoadNetwork * rn);
        void weightDirection2(GCRoadNetwork * rn);
        void weightDirection3(GCRoadNetwork * rn);
        void smoothSimilarity(GCRoadNetwork * rn, int iterations);
        void weightTopology();
        void computeSimilarity(GCRoadNetwork * rn);
        void normalizeValues();
        void computeSpeed();
        void snapValues();
        void computeConfidence();
        int  numberPoints();
        void setEvalParams(GCEvalParams * ep);
        GCPoint * getPointAt(int idx);

    private:
        vector <GCPoint*> * points;
        GCEvalParams * eval_params;
};

#endif
