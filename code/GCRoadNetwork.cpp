#include "GCRoadNetwork.h"



GCRoadNetwork::GCRoadNetwork()
{
    edges=new vector<GCEdge*>();
    edges->reserve(10000);
}

GCRoadNetwork::~GCRoadNetwork()
{
    for(int i=0; i<edges->size(); i++)
    {
        GCEdge * e = edges->at(i);
        delete e;
    }
    delete edges;
    delete rtree;
}

void GCRoadNetwork::addEdge(GCEdge * e)
{
    edges->push_back(e);
    edges_map[e->getId()]=e;
}

void GCRoadNetwork::indexEdges()
{
    rtree = new geos::index::strtree::STRtree();

    for(int i=0;i<edges->size();i++)
    {
        //cout << edges->at(i)->getWKT() << endl << endl;
  //      try
    //    {
                geos::geom::Geometry * ggg = (edges->at(i)->getGeometry());

                const geos::geom::Envelope * env = ggg->getEnvelopeInternal();
                rtree->insert(env,edges->at(i));//,(void *)edges->at(i)->getGeometry());
/*        }
        catch()
        {


        }

*/
    }

}

void GCRoadNetwork::setStartEndNodeForEdge(int index, int start, int end)
{
    edges_map[index]->startnode=start;
    edges_map[index]->endnode=end;
}

void GCRoadNetwork::dump()
{
    cout << "number of edges=" << edges->size() << endl;
    for(int i=0;i<edges->size();i++)
    {
        cout << "#"<< i << " numpoints: " << (edges->at(i))->numberPoints()  << endl;
    }
}

vector <GCEdge*>  GCRoadNetwork::findEdgesByRadius(GCPoint * p, int radius)
{
    vector <GCEdge*> ret;
    //building the bbox polygon
    CoordinateArraySequence  * pol_seq=new CoordinateArraySequence();
    pol_seq->add(Coordinate((p->x)-radius, (p->y)-radius));
    pol_seq->add(Coordinate((p->x)-radius, (p->y)+radius));
    pol_seq->add(Coordinate((p->x)+radius, (p->y)+radius));
    pol_seq->add(Coordinate((p->x)+radius, (p->y)-radius));
    pol_seq->add(Coordinate((p->x)-radius, (p->y)-radius));
    GeometryFactory factory;
    Polygon * pol=factory.createPolygon(factory.createLinearRing(pol_seq), NULL);



    WKTWriter * wkt_writer=new WKTWriter();
    string wkt = wkt_writer->write(pol);

    //cout << "WKT;" << wkt << endl;

    vector <void*>  vvv;

    this->rtree->query(pol->getEnvelopeInternal(), vvv);
    for(int i =0; i< vvv.size(); i++)
    {
        GCEdge * e = (GCEdge*)vvv.at(i);
        ret.push_back(e);
    }

/*
    for(int i =0; i < this->edges->size(); i++)
    {
        if(this->edges->at(i)->getGeometry()->intersects(pol))
        {
            ret.push_back(this->edges->at(i));
        }
    }
*/

    //cout << "# edges matched:" << ret.size() << endl;
    delete pol;
    delete wkt_writer;


    return ret;
}

int GCRoadNetwork::numberEdges()
{
    return edges->size();
}

GCEdge * GCRoadNetwork::getEdgeAt(int idx)
{
    return (edges->at(idx));
}
