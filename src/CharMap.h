#ifndef charMap_H_INCLUDED
#define charMap_H_INCLUDED

struct dot
{
    dot(){}
    dot(unsigned _x, unsigned _y){x = _x; y = _y;}
    unsigned x,y;
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
    bool initMap(unsigned heigth, unsigned width);
    bool fillRect(dot a, dot b);
    bool fillMapFromFile(const char* filePath);

    bool isFree(dot a)const;
    bool isChecked(dot a)const;
    bool isFreeAndUncheckd(dot a)const;
    void markAsChecked(dot a)const;
private:
    unsigned heigth;
    unsigned width;
    char ** map;
};

#endif // charMap_H_INCLUDED
