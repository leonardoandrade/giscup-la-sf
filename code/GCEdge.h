//GCEdge


#ifndef GCEDGE_H
#define GCEDGE_H

#include "geos/geom/Coordinate.h"
#include "geos/geom/CoordinateArraySequence.h"
#include "geos/geom/LineString.h"
#include "geos/geom/LinearRing.h"
#include "geos/geom/GeometryFactory.h"

#include "geos/io/WKTWriter.h"

using namespace geos::geom;
using namespace geos::io;
using namespace std;

class GCEdge
{
    public:
        GCEdge();
        GCEdge(int _id,   float _length, int _startnode, int _endnode, float _cost);
        ~GCEdge();
        void setId(int);

        string getWKT();
        int getId();
        void addPoint(float x, float y);
        void addPoint(double x, double y);
        void addPoint(int x, int y);
        float * getPointAt(int index);
        void buildGeometry();
        int numberPoints();
        float getLength();
        void dump();
        LineString * getGeometry();
        Coordinate getStartPoint();
        Coordinate getEndPoint();
        CoordinateSequence * getCoordinateSequence();
        int startnode;
        int endnode;

    private:
        int id;
        float length;



        LineString * geometry;
        CoordinateArraySequence * seq;
        Coordinate start_point;
        Coordinate end_point;


};

#endif
