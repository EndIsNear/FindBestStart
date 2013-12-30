#ifndef BOOLMAP_H_INCLUDED
#define BOOLMAP_H_INCLUDED

struct dot
{
    dot(unsigned _x, unsigned _y){x = _x; y = _y;}
    unsigned x,y;
};

class boolMap
{
public:
    boolMap();
    ~boolMap();

    void printMap();
    bool initMap(unsigned heigth, unsigned width);
    bool fillRect(dot x, dot y);
    bool fillMapFromFile(const char* filePath);
private:
    unsigned heigth;
    unsigned width;
    bool ** map;
};

#endif // BOOLMAP_H_INCLUDED
