#pragma once

#include "ASource.hpp"

#include <Basics/Vector3D.hpp>

#include <cmath>

namespace RayTracer
{

    class AmbientIllumination : public ASource
    {
    public:
        AmbientIllumination(const Math::Vector3D &color = Math::Vector3D(255. / 3, 255. / 3, 255. / 3));

        std::optional<Math::Vector3D> getColor(const Ray &, const Math::Vector3D &, double,
                                               const std::vector<std::shared_ptr<Math::AFigure>> &);
    };

}
