#ifndef UTILS
#define UTILS

#include"../2d/array_2d/array_2d.h"
#include"paper_layer.h"

namespace utils
{

inline double lerp(double x, double y, double s)
{
    return x * (1-s) + y * s;
}

inline double clamp(double x, double min, double max)
{
    if(x > max) x = max;
    else if(x < min) x = min;
    return x;
}

inline double smoothstep(double edge0, double edge1, double x)
{
    x = clamp((x-edge0)/(edge1-edge0), 0.0, 1.0);
    return x*x*x*(x*(x*6-15)+10);
}

double text2d(const _2d::array_2d<double> &tex, _2d::Point_2d<double> p)
{
    int x = p.x, y = p.y;
    double f00 = tex[x][y];
    double f10 = tex[x+1][y];
    double f01 = tex[x][y+1];
    double f11 = tex[x+1][y+1];
    double a = p.x - x, b = p.y - y;
    return f00*(1-a)*(1-b)
         + f01*(1-a)*b
         + f10*a*(1-b)
         + f11*a*b;
}

}

#endif
