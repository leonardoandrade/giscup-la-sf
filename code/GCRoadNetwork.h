#include "GC.h"



#ifndef GCROADNETWORK_H
#define GCROADNETWORK_H

using namespace std;

class GCRoadNetwork
{
    public:
        GCRoadNetwork();
        ~GCRoadNetwork();
        void indexEdges();
        void addEdge(GCEdge * e);
        int findNearestEdge(GCPoint p);
        void dump();
        int numberEdges();
        GCEdge * getEdgeAt(int idx);
    private:
        vector <GCEdge*> * edges;
};

#endif
