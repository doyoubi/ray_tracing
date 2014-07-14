#ifndef DYB_OBJ
#define DYB_OBJ

#include <cmath>
#include <limits>
#include "../Eigen/Dense"
#include "../2d/2d.h"
#include "settings.h"
#include "debug.h"
#include "utils.h"
#include "intersect.h"
#include "material.h"


namespace dyb{

    using Eigen::Vector3d;
    using std::abs; 
    using std::tan;

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


    struct Geometry
    {
        virtual IntersectResult intersect(const Ray & ray) const = 0;
        virtual RGB sample(const Ray & ray, const IntersectResult & result) const = 0;
    };


    class SinglePlane : public Geometry
    {
    private:
        Plane plane;

    public:
        const MaterialStrategy * material;

        SinglePlane(Vector3d normal, Vector3d point, const MaterialStrategy * _material)
            : plane(normal, point), material(_material)
        {
            debugCheck(material != nullptr, __FILE__, __LINE__, "material is null");
        }

        IntersectResult intersect(const Ray & ray) const
        {
            return plane.intersect(ray);
        }

        RGB sample(const Ray & ray, const IntersectResult & result) const
        {
            return material->sample(ray, result.position, result.normal);
        }
    };

    class Ball : public Geometry
    {
    private:
        Sphere sphere;

    public:
        const MaterialStrategy *  material;

        Ball(Vector3d center, double radius, const MaterialStrategy * _material)
            : sphere(center, radius), material(_material)
        {
            debugCheck(material != nullptr, __FILE__, __LINE__, "material is null");
        }

        IntersectResult intersect(const Ray & ray) const
        {
            return sphere.intersect(ray);
        }

        RGB sample(const Ray & ray, const IntersectResult & result) const
        {
            return material->sample(ray, result.position, result.normal);
        }
    };

}

#endif
