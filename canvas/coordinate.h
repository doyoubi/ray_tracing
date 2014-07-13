#ifndef DYB_COORD
#define DYB_COORD


#include "../Eigen/Dense"
#include "debug.h"
#include <cmath>

namespace dyb
{

    using Eigen::Vector3d;
    using std::tan;
    using std::abs;

    struct Coordinate // right hand coordinate
    {
        Vector3d forward;
        Vector3d up;
        Vector3d right;
        Vector3d c;       // center
        Coordinate(Vector3d _forward, Vector3d _up, Vector3d center)
            : forward(_forward), up(_up), right(-forward.cross(up).normalized()),
              c(center)
        {
            if(abs(forward.dot(up)) > errorThreshold)
            {
                std::cerr<<"Coordinate vector forward and up are not perpendicular!"<<endl;
            }
            if(abs(forward.norm()-1) > errorThreshold)
            {
                std::cerr<<"Coordinate vector forward is not normalized!"<<endl;
            }
            if(abs(up.norm()-1) > errorThreshold)
            {
                std::cerr<<"Coordinate vector up is not normalized!"<<endl;
            }
        }
    };

    struct Camera : public Coordinate
    {
        double xfov, yfov;      // radius
        double screenDistance;

        Camera(Vector3d _forward, Vector3d _up, Vector3d center,
               double _xfov, double _yfov, double _screenDistance)
            : Coordinate(_forward, _up, center),
              xfov(_xfov), yfov(_yfov), screenDistance(_screenDistance)
        {
            debugCheck(0<= xfov && xfov<= M_PI, __FILE__, __LINE__, "invalid xfov");
            debugCheck(0<= yfov && yfov<= M_PI, __FILE__, __LINE__, "invalid yfov");
            debugCheck(0<= screenDistance, __FILE__, __LINE__, "invalid screenDistance");
        }

        Vector3d generateRayDirection(double Nx, double Ny)
        {
            // normalized x y required, -1 <= x <= 1 , -1 <= y <= 1, 
            debugCheck(abs(Nx) <=1 && abs(Ny) <= 1,
                __FILE__, __LINE__,
                "parameter x or y of Camera::generateRay are not normalized!");
            double sx = Nx * screenDistance * tan(xfov/2);
            double sy = Ny * screenDistance * tan(yfov/2);
            return (forward * screenDistance + sx * right + sy * up).normalized();
        }
    };

}

#endif