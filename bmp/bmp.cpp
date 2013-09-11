#include"bmp.h"
#include"../test/test.h"
#include<fstream>
using std::fstream;
using std::ios;
#include<cstring>
using std::strlen;

namespace _bmp{

    BmpFile::BmpFile(const char * const filename)
    {
        validate(filename != 0 && strlen(filename) != 0,
            "invalid filename pointer or empty filename when opening bmp");

        fstream bmpfile("test.bmp", ios::in|ios::out|ios::binary);
        validate(bmpfile.good(), "fail to open bmp");

        bmpfile.read( (char*) &filehead, sizeof(filehead) );
        validate( (filehead.type1 == 'B' && filehead.type2 == 'M')
               || (filehead.type2 == 'b' && filehead.type2 == 'm')
                  ,"not bmp file" );

        bmpfile.read( (char*) &infohead, sizeof(infohead) );
        validate(channels != 1 && channels != 3, "channels is not 1 or 3");
        validate(infohead.width > 0 || infohead.height > 0, "invalid width or height of bmp");

        channels = infohead.bitColor / 8;
        int modbytes = (infohead.width * channels) % 4;
        step = modbytes ? ((infohead.width*channels)-modbytes+4) : (infohead.width*channels);

        bmpfile.seekg(infohead.startPosition);
        pData = new unsigned char[step * infohead.height];
        for(int i = infohead.height-1; i >= 0; i--)
            bmpfile.read( (char*)(pData + i*step), step * sizeof(unsigned char) );
        
        bmpfile.close();
    }

    BmpFile::~BmpFile()
    {
        delete[] pData;
    }

// BmpImage
BmpImage::BmpImage(const char * const filename) : bmpfile(filename)
{
    validate(bmpfile.channels == 3, "channels of bmpfile is not 3");
    Image::create(bmpfile.infohead.width, bmpfile.infohead.height);
    save_bmpfile_to_image();
}

void BmpImage::save(const char * const filename)
{
    save_image_to_bmpfile();
}

void BmpImage::save_bmpfile_to_image()
{
    for(int y = 0; y < bmpfile.infohead.height-1; ++y)
        for(int x = 0; x < bmpfile.infohead.width-1; ++x)
        {
            (*this)[x][y].a = 255;
            (*this)[x][y].b = bmpfile.pData[y*bmpfile.step + x*bmpfile.channels];
            (*this)[x][y].g = bmpfile.pData[y*bmpfile.step + x*bmpfile.channels + 1];
            (*this)[x][y].r = bmpfile.pData[y*bmpfile.step + x*bmpfile.channels + 2];
        }

    bmpfile.infohead.width = get_width();
    bmpfile.infohead.height = get_height();
}

void BmpImage::save_image_to_bmpfile()
{
    for(int y = 0; y < bmpfile.infohead.height; ++y)
        for(int x = 0; x < bmpfile.infohead.width; ++x)
        {
            bmpfile.pData[y*bmpfile.step + x*bmpfile.channels] = (*this)[x][y].b;
            bmpfile.pData[y*bmpfile.step + x*bmpfile.channels + 1] = (*this)[x][y].g;
            bmpfile.pData[y*bmpfile.step + x*bmpfile.channels + 2] = (*this)[x][y].r;
        }
}

BmpImage::~BmpImage(){}

}
