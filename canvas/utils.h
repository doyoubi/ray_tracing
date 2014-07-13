#ifndef UTILS
#define UTILS


namespace dyb
{
    
    inline double angToRad(double angle)
    {
        return angle * M_PI / 180;
    }

    inline double radToAng(double radius)
    {
        return 180 * radius / M_PI;
    }

}

#endif
