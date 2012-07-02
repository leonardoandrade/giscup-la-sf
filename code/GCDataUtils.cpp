#include "GCDataUtils.h"

#include <stdlib.h>
#include <algorithm>
#include <proj_api.h>

vector<string> split_line(const char *str, char c = ' ')
{
    vector<string> result;

    while(1)
    {
        const char *begin = str;

        while(*str != c && *str)
                str++;

        result.push_back(string(begin, str));

        if(0 == *str++)
                break;
    }
    return result;
}


void GCDataUtils::CreateRoadNetworkFromEdgeFile(GCRoadNetwork * rn, const string file_path, const bool convert_to_google_mercator)
{
    projPJ pj_4326, pj_900913;
    if (!(pj_4326 = pj_init_plus("+proj=longlat +ellps=WGS84 +datum=WGS84")))
    {
        exit(1);
    }
    if(!(pj_900913 = pj_init_plus("+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m")))
    {
        exit(1);
    }


    string line;
    ifstream myfile(file_path.c_str());
    if (myfile.is_open())
    {
        int count_lines=0;
        while ( myfile.good() )
        {
            getline (myfile,line);
            vector<string> tok=split_line(line.c_str(),'^');
            if(tok.size()<7)
            {
                continue;
            }
            GCEdge * e=new GCEdge(atoi(tok[0].c_str()), tok[1], tok[2], atof(tok[3].c_str()), 0, 0 , 0);
            for(int i=4; i<tok.size();i+=2)
            {
                double x=atof(tok[i+1].c_str());
                double y=atof(tok[i].c_str());
                //cout << x << ":" << y << endl;
                x *= DEG_TO_RAD;
                y *= DEG_TO_RAD;
                //cout << x << ":" << y << endl;
                if(convert_to_google_mercator)
                {
                    int p = pj_transform(pj_4326, pj_900913, 1, 1, &x, &y, NULL );
                    //cout << "p:" << p << endl;
                }

                //cout << x << ":" << y << endl;
                //cout << endl;
                e->addPoint((float)x,(float)y);
            }
            e->buildGeometry();
            rn->addEdge(e);
            count_lines++;


            //if(count_lines > 100){ break; }
            //cout << line << endl
        }
        myfile.close();
    }
    else
    {
      cout << "Unable to open file";
      return;
    }
}


void  GCDataUtils::WriteRoadNetworkToSQLFile( GCRoadNetwork * rn, const string file_name)
{

    int COMMIT_INTERVAL=1000;
    ofstream f;
    f.open (file_name.c_str());

    int n_edges=rn->numberEdges();
    f << "delete from  t_giscup_edge;\n";
    f << "BEGIN WORK;\n";
    char sql [200000];
    string name="";
    string tmp="";
    GCEdge * e=NULL;
    for(int i=0; i<n_edges; i++)
    {
        tmp="insert into t_giscup_edge(name, type, the_geom) values('%s', '%s', st_setsrid('%s',900913))\n";
        e = rn->getEdgeAt(i);
        name=e->getName();
        replace(name.begin(), name.end(), '\'', ' ');
        sprintf (sql, tmp.c_str(), name.c_str(), e->getType().c_str(), e->getWKT().c_str());
        f << sql;

        if(i%COMMIT_INTERVAL==0)
        {
            f << "END WORK;\n";
            f << "BEGIN WORK;\n";
        }


    }
    f << "END WORK;\n";
    f.close();
    return;
}


void GCDataUtils::CreatePointsTrackFromFile(GCPointsTrack * pt, const string file_name,  const bool convert_to_google_mercator)
{
    projPJ pj_4326, pj_900913;
    if (!(pj_4326 = pj_init_plus("+proj=longlat +ellps=WGS84 +datum=WGS84")))
    {
        exit(1);
    }
    if(!(pj_900913 = pj_init_plus("+proj=merc +a=6378137 +b=6378137 +lat_ts=0.0 +lon_0=0.0 +x_0=0.0 +y_0=0 +k=1.0 +units=m")))
    {
        exit(1);
    }



}

void GCDataUtils::WritePointsTrackToFile(GCPointsTrack * pt, const string file_name)
{

}
