#include "GC.h"

#ifndef GCPOINT_H
#define GCPOINT_H
#include <iostream>
#define EVALUATED_EDGES 6
using namespace std;
class GCPoint
{

    public:
        GCPoint(int _id, double _x, double _y);
         ~GCPoint();
        string asWKT();
        string toStr();
        void dump();
        //members public, for less lines of code...
        int id;
        double x;
        double y;
        int edge;
        GCEdge * edge_obj;
        float confidence;
        int num_edges;
        float speed;
        int   edges_ids[EVALUATED_EDGES];
        float edges_distances[EVALUATED_EDGES];
        float edges_direction_weight[EVALUATED_EDGES];
        float edges_adjacency_weight[EVALUATED_EDGES];
        float edges_similarity[EVALUATED_EDGES];
        float edges_confidence[EVALUATED_EDGES];
        GCEdge * edges[EVALUATED_EDGES];
        GCEdge * best_edge;
};

#endif
