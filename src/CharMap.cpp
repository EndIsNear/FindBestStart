#include <cstdlib>
#include <iostream>
#include <fstream>

#include "charMap.h"

using namespace std;

charMap::charMap()
{
    this->heigth = 0;
    this->width = 0;
    this->map = NULL;
}

charMap::~charMap()
{
    for(unsigned cnt = 0; cnt < this->width; cnt++)
    {
        delete[] this->map[cnt];
    }
    delete[] this->map;
}

void charMap::printMap()const
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
            if(this->map[cnt2][cnt - 1] == 1)//1 - border
            {
                cout << (char)219;
            }
            else if(this->map[cnt2][cnt - 1] == 0)//0 - free
            {
                cout << " ";
            }
            else if(this->map[cnt2][cnt - 1] == 2)//2 - checked
            {
                cout << "x";
            }
            else if (this->map[cnt2][cnt - 1] == 3)//3 - start position
            {
                cout << "S";
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

bool charMap::initMap(unsigned heigth, unsigned width)
{
    this->heigth = heigth + 2;
    this->width = width + 2;
    this->map = new(nothrow) char*[this->width];
    if(!this->map)
    {
        return false;
    }
    for(unsigned cnt = 0; cnt < this->width; cnt++)
    {
        this->map[cnt] = new(nothrow) char[this->heigth];
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

bool charMap::fillRect(dot a, dot b)
{
    if(a.x < 0 || b.x >= this->width || a.y < 0 || b.y >= this->heigth)
    {
        return false;
    }
    for(unsigned i = a.x; i <= b.x; i++)
        for(unsigned j = a.y; j <= b.y; j++)
        {
            this->map[i][j] = 1;
        }

    return true;
}

bool charMap::fillMapFromFile(const char* filePath)
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

bool charMap::isFree(dot a)const
{

    return !this->map[a.x + 1][a.y + 1];
}

bool charMap::isChecked(dot a)const
{
    return this->map[a.x + 1][a.y + 1] == 2;
}

bool charMap::isFreeAndUncheckd(dot a)const
{
    return this->isFree(a) && !this->isChecked(a);
}

void charMap::markAsChecked(dot a)const
{
    this->map[a.x + 1][a.y + 1] = 2;
}

ostream& operator<<(ostream& stream, const dot& dot)
{
    stream << "(" << dot.y <<", " << dot.x << ")";
    return stream;
}
