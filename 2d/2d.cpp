#include"2d.h"
#include<iostream>
using std::ostream;
using std::hex;

namespace _2d
{

#define DEBUG
#ifdef DEBUG
    ostream & operator<<(ostream & out, const ARGB & argb)
    {
        out<< hex << argb.a << argb.r << argb.g << argb.b <<' ';
        return out;
    }
#endif

}
