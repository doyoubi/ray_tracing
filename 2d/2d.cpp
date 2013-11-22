#include"2d.h"
#include<iostream>
using std::ostream;
using std::hex;

namespace _2d
{
    Point_2d::Point_2d(int _x, int _y) : x(_x), y(_y) {}

    const Point_2d operator + (Point_2d lhs, Point_2d rhs)
    { return Point_2d(lhs.x+rhs.x, lhs.y+rhs.y); }

    const Point_2d operator - (Point_2d lhs, Point_2d rhs)
    { return Point_2d(lhs.x-rhs.x, lhs.y-rhs.y); }

    const int operator * (Point_2d lhs, Point_2d rhs)
    { return lhs.x*rhs.x + lhs.y*rhs.y; }

    const Point_2d operator * (Point_2d lhs, int rhs)
    { return Point_2d(lhs.x*rhs, lhs.y*rhs); }

    const Point_2d operator * (int lhs, Point_2d rhs)
    { return rhs * lhs; }

    const bool operator == (Point_2d lhs, Point_2d rhs)
    { return lhs.x == rhs.x && lhs.y == rhs.y; }

    const Point_2d & Point_2d::operator = (Point_2d rhs)
    {
        this->x = rhs.x; this->y = rhs.y;
        return *this;
    }

#define DEBUG
#ifdef DEBUG
    ostream & operator<<(ostream & out, const ARGB & argb)
    {
        out<< hex << argb.a << argb.r << argb.g << argb.b <<' ';
        return out;
    }
#endif

}
