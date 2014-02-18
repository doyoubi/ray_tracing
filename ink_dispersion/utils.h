#ifndef UTILS
#define UTILS

namespace utils
{

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

}

#endif
