#include <iostream>
#include <vector>


using namespace std;




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



int main()
{
    string x = "as armas e os baroes assinalados";
    vector<string> tok=split_line(x.c_str(),' ');

    for(int i=0; i<tok.size();i++)
    {
        cout << "#" << i << ": " << tok[i] << endl;

    }
}
