#ifndef DYB_OBJ
#define DYB_OBJ

#include <cmath>
#include <limits>
#include "../Eigen/Dense"
#include "../2d/2d.h"
#include "settings.h"
#include "debug.h"
#include "utils.h"


namespace dyb{

    using Eigen::Vector3d;
    using std::abs; 
    using std::tan;

    const double errorThreshold = 0.0000001;

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
        const Intersectable * const geometry;
        double                      distance;
        Vector3d                    position;
        Vector3d                    normal;

        IntersectResult(const Intersectable * const _geometry,
                        double                      _distance,
                        Vector3d                    _position,
                        Vector3d                    _normal)
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
        virtual IntersectResult intersect(const Ray & ray) const = 0;
    };

    struct MaterialStrategy
    {
        virtual RGB sample(const Ray & ray, const Vector3d & position, const Vector3d & normal);
    };

    struct Plane : public Intersectable
    {
        Vector3d n;
        Vector3d p;  // an arbitrary point on the surface

        Plane(Vector3d normal, Vector3d point)
            : n(normal), p(point)
        {
            debugCheck(abs(n.norm()-1) < errorThreshold,
                __FILE__, __LINE__, "normal vector not normalized");
        }

        IntersectResult intersect(const Ray & ray) const
        {
            if(n.dot(ray.d) >= 0) return noHit;
            double t = (p - ray.o).dot(n) / n.dot(ray.d);
            Vector3d intersectPoint = ray.getPoint(t);
            return IntersectResult(this, t, intersectPoint, n);
        }
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

        IntersectResult intersect(const Ray & ray) const
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
                                   direction.normalized());
        }
    };

}

#endif
