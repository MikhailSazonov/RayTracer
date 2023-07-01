#pragma once

#include <Figures/AFigure.hpp>
#include <Illumination/LightSources/ISource.hpp>

#include <memory>
#include <vector>

namespace RayTracer
{
    using Objects = std::vector<std::shared_ptr<Math::AFigure>>;
    using Sources = std::vector<std::shared_ptr<ISource>>;

    struct Scene
    {
        Objects objects_;
        Sources lights_;
    };

}

