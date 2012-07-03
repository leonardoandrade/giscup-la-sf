#include "GCRoadNetwork.h"


GCRoadNetwork::GCRoadNetwork()
{
    edges=new vector<GCEdge*>();
    edges->reserve(10000);
}

GCRoadNetwork::~GCRoadNetwork()
{
    delete edges;
}

void GCRoadNetwork::addEdge(GCEdge * e)
{
    edges->push_back(e);
}

void GCRoadNetwork::indexEdges()
{
    //TODO
}

void GCRoadNetwork::dump()
{
    cout << "number of edges=" << edges->size() << endl;
    for(int i=0;i<edges->size();i++)
    {
        cout << "#"<< i << " numpoints: " << (edges->at(i))->numberPoints()  << endl;
    }
}

int GCRoadNetwork::findNearestEdge(GCPoint p)
{
    //TODO
}

int GCRoadNetwork::numberEdges()
{
    return edges->size();
}

GCEdge * GCRoadNetwork::getEdgeAt(int idx)
{
    return (edges->at(idx));
}
