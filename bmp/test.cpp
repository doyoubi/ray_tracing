#include<iostream>
using std::cout;
using std::endl;
#include"bmp.h"
using _bmp::BmpFile;
using _bmp::BmpImage;
#include"../2d/2d.h"
using _2d::ARGB;

int main()
{
    cout<<endl;

    BmpFile bmpfile("test.bmp");
    cout<< bmpfile.filehead.type1<< bmpfile.filehead.type2 << endl;
    for(int j = 0; j < 3; ++j)
    {
        for(int i = 0; i < 9; ++i)
            cout<< (int)(bmpfile.pData[bmpfile.step*j + i]) << ' ';
        cout<< endl;
    }
    cout<<endl;

    BmpImage bmpimage("test.bmp");
    ARGB color = bmpimage[0][0];
    for(int j = 0; j < 3; ++j)
    {
        for(int i = 0; i < 3; ++i)
        {
            color = bmpimage[i][j];
            cout<< (int)color.b << ' '
                << (int)color.g << ' '
                << (int)color.r << ' ';
        }
        cout<<endl;
    }
    cout<<endl;
    cout<< bmpimage.get_width() << ' ' 
        << bmpimage.get_height() <<endl;

    bmpimage.save("savetest.bmp");
    BmpImage test_save("savetest.bmp");
    cout<< bmpfile.filehead.type1<< bmpfile.filehead.type2 << endl;
    cout<< bmpimage.get_width() << ' ' 
        << bmpimage.get_height() <<endl;

    return 0;
}
