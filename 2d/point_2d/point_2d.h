#ifndef POINT2D
#define POINT2D

#include<cmath>

namespace _2d
{

template<class T>
T abs(T num)
{ return num >= 0? num : -num; }

template<class T>
class Point_2d
{ 
public: 
    T x, y;
    Point_2d(T _x, T _y):x(_x), y(_y) {}
    Point_2d(){}
    double norm()const
    {
        return std::sqrt(x*x + y*y);
    }

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

    Point_2d & operator /= (T rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    Point_2d & operator = (const Point_2d & rhs)
    {
        x = rhs.x; y = rhs.y;
        return *this;
    }

    friend bool operator == (const Point_2d & lhs, const Point_2d & rhs)
    { 
        return abs(lhs.x - rhs.x) < 0.000001
            && abs(lhs.y - rhs.y) < 0.000001;
    }
};

// hack
template<class T>
Point_2d<T> create_point(T x, T y)
{ return Point_2d<T>(x, y); }

template<class LHS, class RHS>
auto operator + (const Point_2d<LHS> &lhs, const Point_2d<RHS> &rhs)
    -> decltype(create_point(lhs.x+rhs.x, lhs.y+rhs.y))
{ return create_point(lhs.x+rhs.x, lhs.y+rhs.y); }

template<class LHS, class RHS>
auto operator - (const Point_2d<LHS> &lhs, const Point_2d<RHS> &rhs)
    -> decltype(create_point(lhs.x-rhs.x, lhs.y-rhs.y)) 
{ return create_point(lhs.x-rhs.x, lhs.y-rhs.y); }

template<class LHS, class RHS>
auto operator * (const Point_2d<LHS> &lhs, const Point_2d<RHS> &rhs)
    -> decltype(lhs.x*rhs.x + lhs.y*rhs.y)
{ return lhs.x*rhs.x + lhs.y*rhs.y; }

template<class LHS, class RHS>
auto operator * (const Point_2d<LHS> &lhs, RHS rhs)
    -> decltype(create_point(lhs.x*rhs, lhs.y*rhs))
{ return create_point(lhs.x*rhs, lhs.y*rhs); }

template<class LHS, class RHS>
auto operator * (LHS lhs, const Point_2d<RHS> &rhs)
    -> decltype(create_point(lhs*rhs.x, lhs*rhs.y))
{ return create_point(lhs*rhs.x, lhs*rhs.y); }

template<class LHS, class RHS>
auto operator / (const Point_2d<LHS> &lhs, RHS rhs)
    -> decltype(create_point(lhs.x/rhs, lhs.y/rhs))
{ return create_point(lhs.x/rhs, lhs.y/rhs); }

#define Vector_2d Point_2d
}

#endif
