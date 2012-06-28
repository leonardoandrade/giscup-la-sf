#include "GCDataUtils.h"
#include <stdlib.h>
#include <pqxx/pqxx>
#include <algorithm>

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


void GCDataUtils::CreateRoadNetworkFromEdgeFile(GCRoadNetwork * rn, const string file_path)
{
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
                e->addPoint(atof(tok[i].c_str()),atof(tok[i+1].c_str()));
            }
            e->buildGeometry();
            rn->addEdge(e);
            count_lines++;

            //if(count_lines > 100){ break; }
            //cout << line << endl;
        }
        myfile.close();
    }
    else
    {
      cout << "Unable to open file";
      return;
    }
}

void  GCDataUtils::WriteNetworkToDatabase( GCRoadNetwork * rn, const string dbname)
{
    pqxx::connection c("dbname=giscup");
    pqxx::work txn(c);
    txn.exec("delete from t_giscup_edge");
    txn.commit();
    int n_edges=rn->numberEdges();

    for(int i=0; i<n_edges; i++)
    {
         char sql [20000];

        pqxx::work txn2(c);

        string tmp="insert into t_giscup_edge(name, type, the_geom) values('%s', '%s', st_setsrid('%s',4326))";

        GCEdge * e = rn->getEdgeAt(i);
        string name=e->getName();
        //cout << "1" << endl;
        replace(name.begin(), name.end(), '\'', ' ');
        //cout << "2" << endl;
        sprintf (sql, tmp.c_str(), name.c_str(), e->getType().c_str(), e->getWKT().c_str());

        txn2.exec(sql);
        /*if(i%1000==0)
        {

            txn2.end();
            pqxx::work txn2(c);
        }*/
        txn2.commit();


    }


}


