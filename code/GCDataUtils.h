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
        static void CreateRoadNetworkFromEdgeFile(GCRoadNetwork * rn, const string file_path, bool convert_to_google_mercator);
        static void CreatePointsTrackFromFile(GCPointsTrack * pt, const string file_name,  bool convert_to_google_mercator);
        static void WriteRoadNetworkToSQLFile(GCRoadNetwork * rn, const string file_name);
        static void WritePointsTrackToFile(GCPointsTrack * pt, const string file_name);
};

#endif
