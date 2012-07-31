#include "GC.h"
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <stdlib.h>

#define MAX_INPUTS 100

#include <iostream>
#include <fstream>
#include <string>

//#define MONTE_CARLO_MODE 1

// for operation timming
double diffclock(clock_t clock1,clock_t clock2)
{
	double diffticks=clock1-clock2;
	double diffms=(diffticks*10)/CLOCKS_PER_SEC;
	return diffms/10;
}


int main(int argc, char ** argv)
{

    if(argc != 4)
    {
        cout << "USAGE: \n\tmapmatch [RoadNetworkInfo_Path] [Input_Path] [Output_Path]\n";
        return 0;
    }


    // Load Road Network to memory
    ostringstream edge_file_path;
    ostringstream edge_start_end_nodes_file_path;
    edge_file_path << argv[1] << "/WA_EdgeGeometry.txt";
    edge_start_end_nodes_file_path << argv[1] << "/WA_Edges.txt";
    cout << "Loading road network from file" << edge_file_path.str() << endl;
    clock_t begin=clock();

    GCRoadNetwork * rn=new GCRoadNetwork();
    GCDataUtils::CreateRoadNetworkFromEdgeFile(rn, edge_file_path.str(), edge_start_end_nodes_file_path.str(), true);
    rn->indexEdges();
    //GCDataUtils::WriteRoadNetworkToSQLFile(rn,"/tmp/boda.txt");

	clock_t end=clock();
	cout << rn->numberEdges() << " edges loaded in " << double(diffclock(end,begin)) << " seconds"<< endl;

#ifdef MONTE_CARLO_MODE
    while(1)
    {
        int x=system("python scripts/generate_random_params_alt.py > params.txt");

#endif

    //Load the inputs
     clock_t begin_classification  =clock();
    for(int i=1; i< MAX_INPUTS; i++)
    {

        ostringstream input_file_path;
        ostringstream output_file_path;
        ostringstream number_padded;
        if(i<10)
        {
            number_padded << "0" << i;
        }
        else
        {
            number_padded << i;
        }
        input_file_path << argv[2] << "/input_" << number_padded.str() << ".txt";
        output_file_path << argv[3] << "/output_" << number_padded.str() << ".txt";

        ifstream my_file(input_file_path.str().c_str());
        if(!my_file.good())
        {
            break;
        }
        clock_t begin=clock();

        //cout << "Processing input in file " << input_file_path.str() << endl;
        GCPointsTrack * pt = new GCPointsTrack();
        GCDataUtils::CreatePointsTrackFromFile(pt, input_file_path.str(), true);

        GCEvalParams * ep = new GCEvalParams();


#ifdef MONTE_CARLO_MODE
        ep->loadFromFile("params.txt");
#endif

        pt->setEvalParams(ep);


        //doing the classification
        pt->findNearestEdges(rn);
        pt->computeSpeed();
        pt->weightDirection3(rn);
        pt->normalizeValues();
        //pt->smoothSimilarity(rn, 1000);
        pt->normalizeValues();
        pt->weightTopology();

        pt->computeSimilarity(rn);
        //pt->weightAdjacency(rn);
        //pt->computeSimilarity(rn);



        GCDataUtils::WritePointsTrackToFile(pt,output_file_path.str());
        clock_t end=clock();
        //cout << pt->numberPoints() << " points processed in " << double(diffclock(end,begin)) << " seconds"<< endl;


        delete pt;
        delete ep;
    }
    end=clock();
    cout <<  "point track classification in " << double(diffclock(end,begin_classification)) << " seconds ("<< double(diffclock(end,begin)) << " s. )" << endl;

#ifdef MONTE_CARLO_MODE

    int y=system("sh eval_params_and_percent_to_csv.sh");

    } //end while(1)
#endif
/*
    cout << "loading to file" << endl;
    GCDataUtils::WriteNetworkToSQLFile(rn,"giscup.txt");
    cout << "done" << endl;
*/
    //rn->dump();

/*
    GCPoint * p = new GCPoint(3.0, 5.0);
    p->dump();
    GCEdge * e = new GCEdge();
    e->addPoint(1.0,1.0);
    e->addPoint(1.0,2.0);
    e->addPoint(3.0,3.0);
    e->buildGeometry();
    e->dump();
    */

    //delete rn; //to keep valgrind happy

}
