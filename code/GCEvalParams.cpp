#include "GCEvalParams.h"



GCEvalParams::GCEvalParams()
{

    //0.37;0.26;0.37;1.91;1.68;1.34

    b_distance=0.5;
    b_direction=0.3;
    b_adjacency=0.2;
    topology_adjacent_same_edge=0.5;
    topology_adjacent_accessible=0.5;
    topology_adjacent_same_streetname=2.0;
}


void GCEvalParams::loadFromFile(string file_path)
{
    ifstream myfile(file_path.c_str());

    string line;
    getline (myfile,line);
    vector <float> params=split_weights_line(line.c_str(), ';');

    b_distance=params[0];
    b_direction=params[1];
    b_adjacency=params[2];
    topology_adjacent_same_edge=params[3];
    topology_adjacent_accessible=params[4];
    topology_adjacent_same_streetname=params[5];
    myfile.close();
}


vector <float> GCEvalParams::split_weights_line(const char *str, char c)
{
    vector<float> result;
    while(1)
    {
        const char *begin = str;

        while(*str != c && *str)
                str++;

        result.push_back(atof(string(begin, str).c_str()));

        if(0 == *str++)
                break;
    }
    return result;
}

string GCEvalParams::toStr()
{
    std::ostringstream ret;
    ret  << b_distance << ";" << b_direction << ";" << b_adjacency << ";" \
    << topology_adjacent_same_edge  <<  ";" <<  topology_adjacent_accessible << ";" <<  topology_adjacent_same_streetname << endl;
    return ret.str();
}
