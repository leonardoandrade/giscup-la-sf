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
    for(int i =0; i< EVALUATED_EDGES; i++)
    {
        this->edges_ids[i]=-1;
        this->edges_distances[i]=-99.0;
        this->edges_direction_wheight[i]=-99.0;
        this->edges_adjacent_similarity[i]=-99.0;
        this->edges_similarity[i]=-99.0;
        this->edges_confidence[i]=1.0;

        this->edges_distance_to_start_point[i]=-99.0;
        this->edges_distance_to_end_point[i]=-99.0;
    }
}

GCPoint::~GCPoint()
{ }

void GCPoint::dump()
{
    std::cout << "x:" << x << " y:" << y << std::endl;
}

string GCPoint::toStr()
{
    std::ostringstream ret;
    ret << "id:" << id << " ";
    for(int i =0; i< EVALUATED_EDGES; i++)
    {
        ret << "[edge #" << i << " id:" << this->edges_ids[i]\
         << " dst:" << this->edges_distances[i]\
         << " dir:" << this->edges_direction_wheight[i]\
         << " adj:" << this->edges_adjacent_similarity[i]\
         << " sim:" << this->edges_similarity[i] <<  "]";
    }
    return ret.str();
}

string GCPoint::asWKT()
{
    std::ostringstream wkt;
    wkt << "POINT(" << x << " " << y << ")";
    return wkt.str();
}
