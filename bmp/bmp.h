#ifndef BMP_H
#define BMP_H

#include"../2d/2d.h"
using _2d::Image;

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

    BmpFileHead filehead;
    BmpInfoHead infohead;
    unsigned char * pData;
    int channels;
    int step;
};

//class BMPimage : public Image
//{
//public:
//    BMPimage(const * char const filename);
//    void open(const * char const filename);
//    void save();
//    //from ancestor Image : ARGB & get_ARGB_on(int x, int y);
//
//    ~BMPimage();
//private:
//    void load_bmpfile();
//    void save_bmpfile_to_image();
//    void save_image_to_bmpfile();
//    BmpFile bmpfile;
//};


}

#endif
