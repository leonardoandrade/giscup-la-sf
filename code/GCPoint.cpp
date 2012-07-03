#include "GCPoint.h"

#include <sstream>
using namespace std;

GCPoint::GCPoint(int _id, double _x, double _y)
{
    id=_id;
    x=_x;
    y=_y;
    edge=-1; //initialize as an invalid edge
    confidence=0.0;
}

GCPoint::~GCPoint()
{ }

void GCPoint::dump()
{
    std::cout << "x:" << x << " y:" << y << std::endl;
}

string GCPoint::asWKT()
{
    std::ostringstream wkt;
    wkt << "POINT(" << x << " " << y << ")";
    return wkt.str();
}
