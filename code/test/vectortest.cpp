#include <iostream>
#include <vector>

using namespace std;


int main()
{
    vector <int> * v=new vector<int>();
    cout << "initial size: " << v->size() << endl;
    v->reserve(5);
    for(int i =0; i<12;i++)
    {
        v->resize(i+1);
        (v->at(i))=i*10;
        cout << "insert #" << i<< endl;
        cout << "size: " << v->size() << endl;
        cout << "capacity: " << v->capacity() << endl;
    }



    for(int i =0 ; i< (v->size()); i++)
    {
        cout << "#" << i << ": "<< v->at(i) << endl;
    }


}

