#ifndef UTILS
#define UTILS

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

}

#endif
