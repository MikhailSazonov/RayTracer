#pragma once

#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include <Figures/AFiniteFigure.hpp>
#include <Transformers/TranslationTransformer.hpp>
#include <Transformers/BaseTransformer.hpp>
#include <Solutions/Quadr.hpp>

#include <iostream>

namespace Math
{
    class Cylinder : public AFiniteFigure
    {
    public:
        Cylinder(const Point3D &, double, double, const Operators::ATransformer &transformer = Operators::BaseTransformer(),
                 size_t color = 0x00FFFF, double specular_coef = 16.);

        std::optional<IntersectParams> innerNormalWithIntersection(const RayTracer::Ray &);

    private:
        void CheckPlaneIntersect(std::optional<double> &, IntersectParams &,
                                 const RayTracer::Ray &, double, double);

        std::optional<double> getQuadrFromRay(std::optional<double> &, const RayTracer::Ray &);

        void MakeABox() override;

    private:
        double radius_;
        double height_;
    };

}

