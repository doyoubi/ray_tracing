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
                  (filehead.type2 == 'b' && filehead.type2 == 'm')
                  ,"not bmp file" );

        bmpfile.read( (char*) &infohead, sizeof(infohead) );
        validate(channels != 1 && channels != 3, "channels is not 1 or 3");
        validate(infohead.width <= 0 || infohead.height <=0, "invalid width or height of bmp")

        channels = infohead.bitColor / 8;
        int modbytes = (infohead.width * channels) % 4;
        int step = modbytes ? ((infohead.width*channels)-modbytes+4) : (infohead.width*channels);

        bmpfile.seekg(infohead.startPosition);
        bmpfile.read( (char*) pData, step * infohead.height * sizeof(unsigned char) );
    }
    BmpFile::~BmpFile()
    {
        delete pData;
    }

}