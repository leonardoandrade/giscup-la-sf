#ifndef GCPOINT_H
#define GCPOINT_H
#include <iostream>

using namespace std;
class GCPoint
{

    public:
        GCPoint(int _id, double _x, double _y);
         ~GCPoint();
        string asWKT();
        void dump();
        //members public, for less lines of code...
        int id;
        double x;
        double y;
        int edge;
        float confidence;


};

#endif
