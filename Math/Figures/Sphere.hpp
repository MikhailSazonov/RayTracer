#pragma once

#include <Basics/Point3D.hpp>
#include <Figures/AFigure.hpp>

#include <iostream>

namespace Math
{
    class Sphere : public AFigure
    {
    public:
        Sphere(const Point3D &, double, const Operators::ATransformer &transformer = Operators::BaseTransformer(),
               size_t color = 0xFF0000, double specular_coef = 64.);

        std::optional<IntersectParams> innerNormalWithIntersection(const RayTracer::Ray &);

    private:
        inline Vector3D getNormalVector(const Point3D &point_on_sphere)
        {
            // NB: we already know from the call of hitsWhere, that point lies on the surface of sphere
            // and don't waste resourses for extra checking
            return point_on_sphere - center_;
        }

    private:
        Point3D center_;
        double radius_;
    };

}

