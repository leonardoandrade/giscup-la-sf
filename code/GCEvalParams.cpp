#include "GCEvalParams.h"



GCEvalParams::GCEvalParams()
{

    //0.37;0.26;0.37;1.91;1.68;1.34
    //0.35;0.32;0.33;0.51;0.07;0.99

    //0.43;=0.43;=0.2;=0.2;0.99;1.62;
    b_distance=0.35;
    b_direction=0.32;
    b_adjacency=0.33;
    topology_adjacent_same_edge=0.51;
    topology_adjacent_accessible=0.07;
    topology_adjacent_same_streetname=0.99;
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
