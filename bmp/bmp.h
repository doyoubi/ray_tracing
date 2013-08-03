#ifndef BMP_H
#define BMP_H

#include"2d.h"
using _2d::Picture;

namespace _bmp{

// Copyright Yu Shiqi , modified by doyoubi
class BmpFile
{
public:
    BmpFile(const char * const filename);
    ~BmpFile();
    class BmpFileHead
    {
    public: char type1,type2;
    };
    class BmpInfoHead
    {
    public:
        unsigned int imageSize;
        unsigned int blank;
        unsigned int startPosition;
        unsigned int    length;
        unsigned int    width;
        unsigned int    height;
        unsigned short    colorPlane;
        unsigned short    bitColor;
        unsigned int    zipFormat;
        unsigned int    realSize;
        unsigned int    xPels;
        unsigned int    yPels;
        unsigned int    colorUse;
        unsigned int    colorImportant;
    };

    unsigned char * pData;
};

class BMPpicture : public Picture
{
public:
    BMPpicture(const * char const filename);
    void open(const * char const filename);
    void save();
    //from ancestor Picture : ARGB & get_ARGB_on(int x, int y);

    ~BMPpicture();
private:
    void load_bmpfile();
    void save_bmpfile_to_picture();
    void save_picture_to_bmpfile();
    BmpFile bmpfile;
};


}

#endif