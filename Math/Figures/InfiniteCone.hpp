#pragma once

#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include <Figures/AInfiniteFigure.hpp>
#include <Transformers/TranslationTransformer.hpp>
#include <Transformers/BaseTransformer.hpp>
#include <Solutions/Quadr.hpp>

#include <iostream>

namespace Math
{
    class InfiniteCone : public AInfiniteFigure
    {
    public:
        InfiniteCone(const Point3D &, double, const Operators::ATransformer &transformer = Operators::BaseTransformer(),
             size_t color = 0x808000, double specular_coef = 16.);

        std::optional<IntersectParams> innerNormalWithIntersection(const RayTracer::Ray &);

    private:
        std::optional<double> getQuadrFromRay(std::optional<double> &, const RayTracer::Ray &);

    private:
        double tan_;
    };

}
