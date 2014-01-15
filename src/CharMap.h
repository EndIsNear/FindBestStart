#ifndef charMap_H_INCLUDED
#define charMap_H_INCLUDED

struct dot
{
    dot(){}
    dot(int _x, int _y){x = _x; y = _y;}
    int x,y;
};
std::ostream& operator<<(std::ostream& stream, const dot& dot);


class charMap
{
public:
    charMap();
    ~charMap();

    //0 - free
    //1 - border
    //2 - checked
    //3 - start position

    void printMap()const;
    bool initMap(int heigth, int width);
    bool fillRect(dot a, dot b);
    bool fillMapFromFile(const char* filePath);

    bool isFree(dot a)const;

    int getHeigth()
    {
        return this->heigth - 2;
    }
    int getWidth()
    {
        return this->width - 2;
    }
private:
    int heigth, width;
    char ** map;
};

#endif // charMap_H_INCLUDED
