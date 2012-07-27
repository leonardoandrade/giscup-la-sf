#include "GC.h"

#ifndef GCEVALPARAMS_H
#define GCEVALPARAMS_H

#include <string>
#include <vector>
#include <sstream>

using namespace std;
class GCEvalParams
{
    public:
        float b_distance;
        float b_direction;
        float b_adjacency;
        float topology_adjacent_same_edge;
        float topology_adjacent_accessible;
        float topology_adjacent_same_streetname;
        GCEvalParams();
        void loadFromFile(string path);
        string toStr();
    private:
        vector <float> split_weights_line(const char *str, char c);

};

#endif
