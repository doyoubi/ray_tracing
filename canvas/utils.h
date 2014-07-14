#ifndef UTILS
#define UTILS

#undef RGB
#include <functional>
#include "../Eigen/Dense"

namespace dyb
{

    using Eigen::Vector3d;
    
    inline double angToRad(double angle)
    {
        return angle * M_PI / 180;
    }

    inline double radToAng(double radius)
    {
        return 180 * radius / M_PI;
    }

    inline Vector3d modulate(const Vector3d & lhs, const Vector3d & rhs)
    {
        return Vector3d(lhs.x() * rhs.x(),
                        lhs.y() * rhs.y(),
                        lhs.z() * rhs.z());
    }

    inline RGB vecToRGB(const Vector3d & color)
    {
        return RGB(color.x(), color.y(), color.y());
    }

    void executeOnce(std::function<void (void)> func)
    {
        static bool completed = false;
        if(completed) return;
        func();
        completed = true;
    }

}

#endif
