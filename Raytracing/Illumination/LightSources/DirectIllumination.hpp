#pragma once

#include "ASource.hpp"

#include <Basics/Vector3D.hpp>
#include <RayTrace.hpp>

#include <CmdLineParser.hpp>

#include <cmath>

namespace RayTracer
{

    class DirectIllumination : public ASource
    {
    public:
        DirectIllumination(const Math::Vector3D &, const Math::Vector3D &color = Math::Vector3D(255., 255., 255.),
                           double diffuse_coef = 1., double specular_coef = 1.);

        std::optional<Math::Vector3D> getColor(const Ray &, const Math::Vector3D &, double,
                                               const Storage::IStorage&);

        bool isShadowed(const Ray&,
        const Storage::IStorage&);

    private:
        Math::Vector3D direction_;
        double diffuse_coef_;
        double specular_coef_;
    };

}

