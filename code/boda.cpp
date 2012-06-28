#include "GC.h"

int main(int argc, char ** argv)
{

    GCRoadNetwork * rn=new GCRoadNetwork();
    cout << "loading road network to memory" << endl;
    GCDataUtils::CreateRoadNetworkFromEdgeFile(rn, argv[1]);
    cout << "loading to database" << endl;
    GCDataUtils::WriteNetworkToDatabase(rn,"giscup");
    cout << "done" << endl;

    //rn->dump();

/*
    GCPoint * p = new GCPoint(3.0, 5.0);
    p->dump();
    GCEdge * e = new GCEdge();
    e->addPoint(1.0,1.0);
    e->addPoint(1.0,2.0);
    e->addPoint(3.0,3.0);
    e->buildGeometry();
    e->dump();
    */
}
