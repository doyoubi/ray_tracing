#ifndef DYB_OBJ
#define DYB_OBJ

#include <cmath>
#include <limits>
#include "../Eigen/Dense"
#include "../2d/2d.h"
#include "settings.h"
#include "debug.h"


namespace dyb{

    using Eigen::Vector3d;
    using std::abs; 
    using std::tan;

    inline double angToRad(double angle)
    {
        return angle * M_PI / 180;
    }

    inline double radToAng(double radius)
    {
        return 180 * radius / M_PI;
    }

    const double errorThreshold = 0.0000001;

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

    struct Ray
    {
        Vector3d o;    // origin
        Vector3d d;    // direction

        Ray(Vector3d origin, Vector3d direction)
            : o(origin), d(direction.normalized())
        {
            if(abs(direction.norm() - 1) > errorThreshold)
            {
                std::cout<< "Construct Ray: direction normalized automatically" <<endl;
            }
        }

        Vector3d getPoint(double t) const
        {
            return o + d * t;
        }
    };

    struct Intersectable;

    struct IntersectResult
    {
        Intersectable * geometry;
        double          distance;
        Vector3d        position;
        Vector3d        normal;

        IntersectResult(Intersectable * _geometry,
                        double          _distance,
                        Vector3d        _position,
                        Vector3d        _normal)
            : geometry(_geometry),
              distance(_distance),
              position(_position),
              normal(_normal)
        {
        }

        bool operator == (const IntersectResult & otherResult) const
        {
            // support comparison with noHit, insideObject
            if(this == &otherResult) return true;
            return geometry == otherResult.geometry
                && distance == otherResult.distance
                && position == otherResult.position
                && normal   == otherResult.normal;
        }
    };

    const IntersectResult noHit = IntersectResult(
        nullptr, std::numeric_limits<double>::infinity(), Vector3d::Zero(), Vector3d::Zero()
    );
    const IntersectResult insideObject = IntersectResult(
        nullptr, std::numeric_limits<double>::quiet_NaN(), Vector3d::Zero(), Vector3d::Zero()
    );


    struct Intersectable
    {
        virtual IntersectResult intersect(const Ray & ray) = 0;
    };

    struct Sphere : public Intersectable
    {
        Vector3d c;    // center
        double   r;    // radius

        Sphere(Vector3d center, double radius)
            : c(center), r(radius)
        {
            debugCheck(r > 0, __FILE__, __LINE__, "nagative radius");
        }

        IntersectResult intersect(const Ray & ray)
        {
            // t = -d*v - sqrt( (d*v)^2 - (v*v - r*r) )
            Vector3d v = ray.o - c;
            double vvSubrr = v.dot(v) - r*r;
            if(vvSubrr <= 0) return insideObject;
            double dDotv = ray.d.dot(v);
            if(dDotv >= 0) return noHit;
            double delta = dDotv * dDotv - vvSubrr;
            if(delta <= 0) return noHit;

            double t = -dDotv - std::sqrt(delta);
            Vector3d intersectPoint = ray.getPoint(t);
            Vector3d direction = intersectPoint - c;
            return IntersectResult(this,
                                   t,
                                   intersectPoint,
                                   direction / direction.norm());
        }
    };

}

#endif
