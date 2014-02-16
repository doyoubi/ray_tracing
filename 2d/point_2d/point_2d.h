#ifndef POINT2D
#define POINT2D

namespace _2d
{

template<class T>
class Point_2d
{ 
public: 
    T x, y;
    Point_2d(T _x, T _y):x(_x), y(_y) {}
    Point_2d(){}
    
    //  operator +  -  *   ==  =
    friend const Point_2d operator + (const Point_2d & lhs, const Point_2d & rhs)
    { return Point_2d(lhs.x+rhs.x, lhs.y+rhs.y); }

    friend const Point_2d operator - (const Point_2d & lhs, const Point_2d & rhs)
    { return Point_2d(lhs.x-rhs.x, lhs.y-rhs.y); }

    friend const T operator * (const Point_2d & lhs, const Point_2d & rhs)
    { return lhs.x*rhs.x + lhs.y*rhs.y; }

    friend const Point_2d operator * (const Point_2d & lhs, T rhs)
    { return Point_2d(lhs.x*rhs, lhs.y*rhs); }
    friend const Point_2d operator * (T lhs, const Point_2d & rhs)
    { return rhs * lhs; }

    Point_2d & operator += (const Point_2d & rhs)
    { 
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Point_2d & operator -= (const Point_2d & rhs)
    { 
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Point_2d & operator *= (T rhs)
    { 
        x *= rhs;
        y *= rhs;
        return *this;
    }

    Point_2d & operator = (const Point_2d & rhs)
    {
        x = rhs.x; y = rhs.y;
        return *this;
    }

    friend bool operator == (const Point_2d & lhs, const Point_2d & rhs)
    { return lhs.x == rhs.x && lhs.y == rhs.y; }

    operator Point_2d<double>()const
    { return Point_2d<double>(this->x, this->y); }
};

#define Vector_2d Point_2d
}

#endif
