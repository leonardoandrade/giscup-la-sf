#include "GC.h"



#ifndef GCROADNETWORK_H
#define GCROADNETWORK_H

#include "geos/geom/CoordinateArraySequence.h"
#include "geos/geom/Polygon.h"
#include "geos/geom/Envelope.h"
#include "geos/index/strtree/STRtree.h"
#include "geos/index/ItemVisitor.h"
#include <map>


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
        vector <GCEdge*>  findEdgesByRadius(GCPoint * p, int radius);
        void setStartEndNodeForEdge(int index, int start, int end);
        GCEdge * getEdgeAt(int idx);
    private:
        vector <GCEdge*> * edges;
        geos::index::strtree::STRtree * rtree;
        map <int, GCEdge*> edges_map;

};

#endif
