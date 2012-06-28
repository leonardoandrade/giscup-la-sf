#include "GC.h"

#ifndef GCDATAUTILS_H
#define GCDATAUTILS_H

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

class GCDataUtils
{
    public:
        static void CreateRoadNetworkFromEdgeFile(GCRoadNetwork * rn, const string file_path);
        static void WriteNetworkToDatabase( GCRoadNetwork * rn, const string dbname);

};

#endif
