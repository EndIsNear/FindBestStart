#include <cstdlib>
#include <iostream>

#include "BoolMap.h"

using namespace std;

boolMap::boolMap()
{
    this->heigth = 0;
    this->width = 0;
    this->map = NULL;
}

boolMap::~boolMap()
{
    for(unsigned cnt = 0; cnt < this->width; cnt++)
    {
        delete[] this->map[cnt];
    }
    delete[] this->map;
}

void boolMap::printMap()
{
    for(unsigned cnt = this->heigth; cnt > 0; cnt--)
    {
        for(unsigned cnt2 = 0; cnt2 < this->width; cnt2++)
        {
            if(this->map[cnt2][cnt - 1])
            {
                cout << (char)219;
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

bool boolMap::initMap(unsigned heigth, unsigned width)
{
    this->heigth = heigth;
    this->width = width;
    this->map = new(nothrow) bool*[this->width];
    if(!this->map)
    {
        return false;
    }
    for(unsigned cnt = 0; cnt < this->width; cnt++)
    {
        this->map[cnt] = new(nothrow) bool[this->heigth];
        if(!this->map[cnt])
        {
            for(unsigned cntForDel = 0; cntForDel < cnt; cntForDel++)
            {
                delete[] this->map[cntForDel];
            }
            return false;
        }
        for(unsigned i = 0; i < heigth; i++)
            this->map[cnt][i] = false;
    }
    return true;
}

bool boolMap::fillRect(dot x, dot y)
{
    if(x.x < 0 || y.x >= this->width || x.y < 0 || y.y >= this->heigth)
    {
        return false;
    }
    for(int i = x.x; i <= y.x; i++)
        for(int j = x.y; j <= y.y; j++)
        {
            this->map[i][j] = true;
        }

    return true;
}

bool boolMap::fillMapFrimFile(const char* filePath)
{

}
