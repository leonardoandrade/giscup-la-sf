#include "GCPoint.h"
#include <iostream>

using namespace std;

GCPoint::GCPoint(float _x, float _y)
{
    x=_x;
    y=_y;
}

GCPoint::~GCPoint()
{ }

void GCPoint::dump()
{
    std::cout << "x:" << x << " y:" << y << std::endl;
}

