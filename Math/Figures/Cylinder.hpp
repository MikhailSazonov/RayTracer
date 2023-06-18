#pragma once

#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include <Figures/AFigure.hpp>
#include <Transformers/TranslationTransformer.hpp>
#include <Transformers/BaseTransformer.hpp>
#include <Solutions/Quadr.hpp>

#include <iostream>

namespace Math
{
    class Cylinder : public AFigure
    {
    public:
        Cylinder(const Point3D &, double, std::optional<double>, const Operators::ATransformer &transformer = Operators::BaseTransformer(),
                 size_t color = 0x00FFFF, double specular_coef = 16.);

        std::optional<IntersectParams> innerNormalWithIntersection(const RayTracer::Ray &);

    private:
        void CheckPlaneIntersect(std::optional<double> &, IntersectParams &,
                                 const RayTracer::Ray &, double, double);

        std::optional<double> getQuadrFromRay(std::optional<double> &, const RayTracer::Ray &);

    private:
        double radius_;
        double height_;
        bool limited_{true};
    };

}

