#include <cstdlib>
#include <iostream>
#include <fstream>

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

bool boolMap::isFree(dot a)
{
    return !(this->map[a.x + 1][a.y + 1]);
}

void boolMap::printMap()
{
    for(unsigned cnt = this->heigth; cnt > 0; cnt--)
    {
        if(cnt > 1 && cnt < this->heigth)
        {
            cout << cnt - 1;
        }
        else
        {
            cout << " ";
        }
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
    cout << "  ";
    for(unsigned cnt = 0; cnt < this->width - 2; ++cnt)
    {
        cout << (char)('A' + cnt);
    }
}

bool boolMap::initMap(unsigned heigth, unsigned width)
{
    this->heigth = heigth + 2;
    this->width = width + 2;
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

    for (unsigned cnt = 0; cnt < this->heigth; cnt++)
    {
        this->map[cnt][this->width - 1] = true;
        this->map[cnt][0] = true;
    }
    for (unsigned cnt = 0; cnt < this->width; cnt++)
    {
        this->map[this->heigth - 1][cnt] = true;
        this->map[0][cnt] = true;
    }

    return true;
}

bool boolMap::fillRect(dot x, dot y)
{
    if(x.x < 0 || y.x >= this->width || x.y < 0 || y.y >= this->heigth)
    {
        return false;
    }
    for(unsigned i = x.x; i <= y.x; i++)
        for(unsigned j = x.y; j <= y.y; j++)
        {
            this->map[i][j] = true;
        }

    return true;
}

bool boolMap::fillMapFromFile(const char* filePath)
{
    dot a(0,0), b(0,0);
    ifstream inFile(filePath);
    if(!inFile)
    {
        cerr << "Cannot open the file - " << filePath << "!" << endl;
        return false;
    }
    inFile >> this->width;
    inFile >> this->heigth;
    this->initMap(this->width, this->heigth);
    while(!inFile.eof())
    {
        inFile >> a.x;
        inFile >> a.y;
        inFile >> b.x;
        inFile >> b.y;
        ++ a.x;
        ++ a.y;
        ++ b.x;
        ++ b.y;
        this->fillRect(a,b);
    }


    inFile.close();
    return true;
}
