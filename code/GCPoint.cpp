#include "GCPoint.h"

#include <sstream>
using namespace std;

GCPoint::GCPoint(int _id, double _x, double _y)
{
    id=_id;
    x=_x;
    y=_y;
    edge=-1; //initialize as an invalid edge
    best_edge=NULL;
    confidence=1.0;
    speed=0.0;
    for(int i =0; i< EVALUATED_EDGES; i++)
    {
        this->edges_ids[i]=-1;
        this->edges_distances[i]=10000;
        this->edges_direction_wheight[i]=0.0;
        this->edges_adjacency_weight[i]=0.0;
        this->edges_similarity[i]=0.0;
        this->edges_confidence[i]=1.0;
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
         << " adj:" << this->edges_adjacency_weight[i]\
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
