#ifndef GCPOINT_H
#define GCPOINT_H

class GCPoint
{

    public:
        GCPoint(float _x, float _y);
         ~GCPoint();
        float x;
        float y;
        void dump();
};

#endif
