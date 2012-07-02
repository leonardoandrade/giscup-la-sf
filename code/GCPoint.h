#ifndef GCPOINT_H
#define GCPOINT_H
#include <iostream>

using namespace std;
class GCPoint
{

    public:
        GCPoint(int _id, float _x, float _y);
         ~GCPoint();
        string asWKT();
        void dump();
        //members public, for less lines of code...
        int id;
        float x;
        float y;
        int edge;
};

#endif
