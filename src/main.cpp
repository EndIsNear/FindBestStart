#include <iostream>
#include <cstdlib>

#include "Utils.h"
#include "heap.h"
using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        if(argc < 2)
        {
            cout << "Too few arguments.Need map file." << endl;
        }
        else
        {
            cout << "Too many arguments.Need only map file." << endl;
        }
        return 1;
    }

//    charMap map;
//    if(!map.fillMapFromFile(argv[1]))
//    {
//        cerr << "Cannot load map!" << endl;
//        return -1;
//    }
//    map.printMap();
//
//    cout << endl;
//
//    Graph<LinkedList<dot> > gr;
//    fromBoolMapToGraph(map, gr);
//    gr.print();
    Heap<int> hp;
    for(int i = 30; i > 0; --i)
        hp.Push(i,i);

    while(!hp.IsEmpty())
        cout << hp.Pop() << endl;

    return 0;
}
