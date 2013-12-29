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

//    boolMap test;
//    test.initMap(10,5);
//    test.fillRect(dot(0,0),dot(0,0));
//    test.fillRect(dot(1,1),dot(2,2));
//    test.fillRect(dot(3,3),dot(4,4));
//    test.fillRect(dot(3,7),dot(4,9));
//    test.printMap();
    return 0;
}
