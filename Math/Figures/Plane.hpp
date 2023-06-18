#pragma once

#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include <Figures/AInfiniteFigure.hpp>

#include <Transformers/TranslationTransformer.hpp>
#include <Transformers/BaseTransformer.hpp>

#include <iostream>

namespace Math
{
    class Plane : public AInfiniteFigure
    {
    public:
        Plane(const Point3D &, const Vector3D &, const Operators::ATransformer &transformer = Operators::BaseTransformer(),
              size_t color = 0x00FF00, double specular_coef = 1.);

        std::optional<IntersectParams> innerNormalWithIntersection(const RayTracer::Ray &);

    private:
        Point3D point_;
        Vector3D normal_;
    };

}

