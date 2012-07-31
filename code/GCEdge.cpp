#include "GCEdge.h"
#include <iostream>


GCEdge::GCEdge()
{
    seq=new CoordinateArraySequence();
}

GCEdge::GCEdge(int _id,  float _length,  int _startnode, int _endnode, float _cost) :
 id(_id), startnode(_startnode), endnode(_endnode)
{
     seq=new CoordinateArraySequence();
}


GCEdge::~GCEdge()
{
    delete seq;
    //delete geometry;
}

Coordinate GCEdge::getStartPoint()
{
    return this->start_point;
}

Coordinate GCEdge::getEndPoint()
{
    return this->end_point;
}





void GCEdge::addPoint(float x, float y)
{
    seq->add(Coordinate(x,y));
}


void GCEdge::addPoint(int x, int y)
{
    seq->add(Coordinate(x,y));
}

void GCEdge::addPoint(double x, double y)
{
    seq->add(Coordinate(x,y));
}

int GCEdge::numberPoints()
{
   return seq->getSize();

}


int GCEdge::getId()
{
    return this->id;
}



string  GCEdge::getWKT()
{
    WKTWriter * wkt_writer=new WKTWriter();
    string wkt = wkt_writer->write(geometry);
    delete wkt_writer;
    return wkt;

}

void GCEdge::buildGeometry()
{
    GeometryFactory factory;
    geometry=factory.createLineString(seq);
    this->start_point=seq->front();
    this->end_point=seq->back();
    //delete seq;
}

CoordinateSequence * GCEdge::getCoordinateSequence()
{
    return seq;
}

LineString * GCEdge::getGeometry()
{
    return geometry;
}

void GCEdge::dump()
{
    cout << "ID: "<< id;
    WKTWriter * wkt_writer=new WKTWriter();
    string wkt = wkt_writer->write(geometry);
    cout << "EDGE WKT= " << wkt << endl;
}

float GCEdge::getLength()
{
    return 1000;
}
