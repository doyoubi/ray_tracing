#ifndef DYB_MATERIAL
#define DYB_MATERIAL

#undef RGB
#include "intersect.h"
#include "debug.h"

namespace dyb
{

    struct MaterialStrategy
    {
        virtual RGB sample(const Ray & ray, 
                           const Vector3d & position,
                           const Vector3d & normal) = 0;
    };

    struct LatticeMaterial : public MaterialStrategy
    {
        double size;

        LatticeMaterial(double _size)
            : size(_size)
        {
            debugCheck(size > 0, __FILE__, __LINE__, "negative size");
        }

        virtual RGB sample(const Ray & ray, const Vector3d & position, const Vector3d & normal)
        {
            int sx = int(position.x() / size);
            int sz = int(position.z() / size);
            unsigned char color = (sx+sz) % 2 ? 255 : 0;
            return RGB(color, color, color);
        }
    };
}

#endif