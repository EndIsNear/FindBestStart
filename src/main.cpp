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

//    boolMap map;
//    map.fillMapFromFile(argv[1]);
//    map.printMap();
//    cout << endl;

    Graph<int> gr;
    gr.AddNode(121);
    gr.print();
    gr.print();
    gr.print();



    return 0;
}
