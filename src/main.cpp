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
    map.fillMapFromFile(argv[1]);
    map.printMap();

    return 0;
}
