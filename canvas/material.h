#ifndef DYB_MATERIAL
#define DYB_MATERIAL

#undef RGB
#include <algorithm>
#include <cmath>
#include "intersect.h"
#include "debug.h"

namespace dyb
{
    using std::max;
    using std::min;
    using std::pow;

    struct MaterialStrategy
    {
        virtual Vector3d sample(const Ray & ray, 
                                const Vector3d & position,
                                const Vector3d & normal) const = 0;
    };

    struct LatticeMaterial : public MaterialStrategy
    {
        double size;
        double reflectiveness;

        LatticeMaterial(double _size, double _reflectiveness)
            : size(_size), reflectiveness(_reflectiveness)
        {
            debugCheck(size > 0, __FILE__, __LINE__, "negative size");
            debugCheck(reflectiveness >= 0, __FILE__, __LINE__, "negative reflectiveness");
        }

        Vector3d sample(const Ray & ray, const Vector3d & position, const Vector3d & normal) const
        {
            int sx = int(position.x() / size);
            int sz = int(position.z() / size);
            double color = (sx+sz) % 2 ? 255.0 : 0.0;
            return Vector3d(color, color, color);
        }
    };

    struct PhongMaterial : public MaterialStrategy
    {
        Vector3d c_diff, c_spec;
        double smoothness, reflectiveness;

        PhongMaterial(Vector3d diffuse_color, Vector3d specular_color,
                      double _smoothness, double _reflectiveness)
            : c_diff(diffuse_color), c_spec(specular_color),
              smoothness(_smoothness), reflectiveness(_reflectiveness)
        {
            debugCheck(smoothness > 0, __FILE__, __LINE__, "negative smoothness");
            debugCheck(reflectiveness >= 0, __FILE__, __LINE__, "negative reflectiveness");
            debugCheck(checkVectorNormalized(c_diff), __FILE__, __LINE__, "diffuse_color not normalized");
            debugCheck(checkVectorNormalized(c_spec), __FILE__, __LINE__, "specular_color not normalized");
        }

        Vector3d sample(const Ray & ray, const Vector3d & position, const Vector3d & normal) const
        {
            Vector3d l = Vector3d(1,1,-1).normalized(); // global light
            Vector3d lightColor = Vector3d(255,255,255);
            double nDotl  = normal.dot(l);
            Vector3d h = (l - ray.d).normalized();
            double nDoth = normal.dot(h);
            Vector3d diffuseTerm = c_diff * max(nDotl, 0.0);
            Vector3d specularTerm = c_spec * pow(max(nDoth, 0.0), smoothness);
            Vector3d color = modulate(lightColor, diffuseTerm + specularTerm);
            color.x() = min(color.x(), 255.0);
            color.y() = min(color.y(), 255.0);
            color.z() = min(color.z(), 255.0);
            return color;
        }
    };

}

#endif