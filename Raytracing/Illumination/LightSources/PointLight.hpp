#pragma once

#include "ASource.hpp"

#include <Basics/Vector3D.hpp>
#include <RayTrace.hpp>

#include <CmdLineParser.hpp>

#include <cmath>

namespace RayTracer
{

    class PointLight : public ASource
    {
    public:
        PointLight(const Math::Point3D &position, const Math::Vector3D &color = Math::Vector3D(255., 255., 255.),
                   double diffuse_coef = 1., double specular_coef = 1.);

        std::optional<Math::Vector3D> getColor(const Ray &, const Math::Vector3D &, double,
                                               const std::vector<std::shared_ptr<Math::AFigure>> &);

        bool isShadowed(const Ray&,
        const std::vector<std::shared_ptr<Math::AFigure>>&);

    private:
        Math::Point3D position_;
        double diffuse_coef_;
        double specular_coef_;
    };

}