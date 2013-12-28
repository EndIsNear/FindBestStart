#ifndef BOOLMAP_H_INCLUDED
#define BOOLMAP_H_INCLUDED

class boolMap
{
public:
    boolMap();
    ~boolMap();


private:
    unsigned heigth;
    unsigned width;
    bool ** map;
};

#endif // BOOLMAP_H_INCLUDED
