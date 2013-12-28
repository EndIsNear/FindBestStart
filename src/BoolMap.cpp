#include "BoolMap.h"
#include <cstdlib>
boolMap::boolMap()
{
    this->heigth = 0;
    this->width = 0;
    this->map = NULL;
}

boolMap::~boolMap()
{
    for(unsigned cnt = 0; cnt < width; cnt++)
    {
        delete[] this->map[cnt];
    }
    delete[] this->map;
}
