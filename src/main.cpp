#include <iostream>
#include <cstdlib>

#include "Utils.h"
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

    charMap map;
    if(!map.fillMapFromFile(argv[1]))
    {
        cerr << "Cannot load map!" << endl;
        return -1;
    }
    map.printMap();
    cout << endl;

    Graph<LinkedList<dot> > gr;
    fromBoolMapToGraph(map, gr);
    //gr.print();

    findBestNodes(gr);

    return 0;
}
