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
    class Cone : public AFigure
    {
    public:
        Cone(const Point3D &, double, std::optional<double>, const Operators::ATransformer &transformer = Operators::BaseTransformer(),
             size_t color = 0x808000, double specular_coef = 16.);

        std::optional<IntersectParams> innerNormalWithIntersection(const RayTracer::Ray &);

    private:
        void CheckPlaneIntersect(std::optional<double> &, IntersectParams &,
                                 const RayTracer::Ray &);

        std::optional<double> getQuadrFromRay(std::optional<double> &, const RayTracer::Ray &);

        void MakeBox() override;

    private:
        double radius_;
        double height_{1.0};
        double max_y_normal_;
        bool limited_{true};
    };

}
