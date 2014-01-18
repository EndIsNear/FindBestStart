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
    for(int cnt = 0; cnt < this->width; cnt++)
    {
        delete[] this->map[cnt];
    }
    delete[] this->map;
}

void charMap::printMap()const
{
    for(int cnt = this->heigth; cnt > 0; cnt--)
    {
        if(cnt > 1 && cnt < this->heigth)
        {
            cout << cnt - 1;
        }
        else
        {
            cout << " ";
        }
        for(int cnt2 = 0; cnt2 < this->width; cnt2++)
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
    for(int cnt = 0; cnt < this->width - 2; ++cnt)
    {
        cout << (char)('A' + cnt);
    }
}

bool charMap::initMap(int heigth, int width)
{
    this->width = width + 2;
    this->heigth = heigth + 2;

    this->map = new(nothrow) char*[this->width];
    if(!this->map)
    {
        return false;
    }
    for(int i = 0; i < this->width; ++i)
    {
        this->map[i] = new(nothrow) char[this->heigth];
        if(!this->map[i])
        {
            return false;
        }
        for(int j = 0; j < this->heigth; ++j)
        {
            this->map[i][j] = 0;
        }
    }

    for(int i = 0; i < this->width; ++i)
    {
        this->map[i][0] = 1;
        this->map[i][this->heigth - 1] = 1;
    }

    for(int i = 0; i < this->heigth; ++i)
    {
        this->map[0][i] = 1;
        this->map[this->width - 1][i] = 1;
    }

    return true;
}

bool charMap::fillRect(dot a, dot b)
{
    if(a.x < 0 || b.x >= this->width || a.y < 0 || b.y >= this->heigth)
    {
        return false;
    }
    for(int i = a.x; i <= b.x; i++)
    {
        for(int j = a.y; j <= b.y; j++)
        {
            this->map[i][j] = 1;
        }
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
    int width, heigth;

    inFile >> width;
    inFile >> heigth;

    if(width < 1 || heigth < 1)
    {
        cerr << "Width > 1 and Heigth > 1" << endl;
        return false;
    }

    this->initMap(heigth, width);
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

ostream& operator<<(ostream& stream, const dot& dot)
{
    stream << "(" <<(char)(dot.x + 'A') <<", " << dot.y + 1 << ")";
    return stream;
}
