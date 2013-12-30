#include <iostream>

#include "BoolMap.h"
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

    boolMap test;
    test.fillMapFromFile(argv[1]);
    test.printMap();

    return 0;
}
