#include"2d.h"
namespace _2d
{

#ifdef DEBUG
    ofstream & operator<<(ofstream & out, const & ARGB argb)
    {
        cout<< hex << rgb.a << rgb.r << rgb.g << rgb.b <<' ';
        return out;
    }
    ofstream & operator<<(ofstream & out, const Image & image)
    {
        for(int n = 0; n < width*height; ++n)
            out<< image.data[n] <<' ';
        out<<endl;
        return out;
    }
#endif

}
