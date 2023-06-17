#pragma once

#include <Figures/AFigure.hpp>
#include <Illumination/LightSources/ISource.hpp>

#include <memory>
#include <vector>

namespace RayTracer
{
    struct Scene
    {
        std::vector<std::shared_ptr<Math::AFigure>> objects_;
        std::vector<std::shared_ptr<ISource>> lights_;
    };

}

