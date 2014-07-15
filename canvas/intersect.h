#ifndef DYB_INTERSECT
#define DYB_INTERSECT


#include "../Eigen/Dense"

namespace dyb
{

    using Eigen::Vector3d;

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
            return geometry == otherResult.geometry
                && distance == otherResult.distance
                && position == otherResult.position
                && normal   == otherResult.normal;
        }

        bool operator != (const IntersectResult & otherResult) const
        {
            return !(*this == otherResult);
        }
    };

    const IntersectResult noHit = IntersectResult(
        nullptr, std::numeric_limits<double>::infinity(), Vector3d::Zero(), Vector3d::Zero()
    );
    const IntersectResult insideObject = IntersectResult(
        nullptr, std::numeric_limits<double>::min(), Vector3d::Zero(), Vector3d::Zero()
    );


    struct Intersectable
    {
        virtual IntersectResult intersect(const Ray & ray) const = 0;
    };

}

#endif