#pragma once

#include <Basics/Vector3D.hpp>
#include <Basics/Point3D.hpp>

namespace RayTracer
{
    class Ray
    {
    public:
        Ray(const Math::Point3D &, const Math::Vector3D &);

        // Modifies the ray, so the ray is reflected
        // NB: we dont check that the point lies on the ray and waste resourses
        // return value: chain call?
        Ray &ReflectInPlace(const Math::Point3D &, Math::Vector3D);

        // Instead of in-place modifiyng, creates a new ray.
        // This could be useful, when the ray is refracted (i.e. we need 2 rays instead of 1 anyway)
        Ray Reflect(const Math::Point3D &, Math::Vector3D);

        // Return a ray with coordinates in A - basis
        inline Ray coordinatesChange(const Math::Operators::Matrix<4, 4> &transform) const
        {
            return Ray(transform * source_, transform * direction_);
        }

        Math::Point3D at(double t) const;

    public:
        Math::Point3D source_;
        Math::Vector3D direction_;
    };

}

