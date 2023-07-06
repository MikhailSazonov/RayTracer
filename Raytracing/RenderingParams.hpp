#pragma once

#include <Basics/Vector3D.hpp>
#include <Figures/Params/IntersectParams.hpp>

namespace RayTracer {
    // Helpful struct
    struct RenderingObjectParameters
    {
        Math::IntersectParams params;
        Math::Vector3D color_reaction;
        double specular_coef;
    };
}
