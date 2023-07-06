#pragma once

#include <Figures/AFigure.hpp>
#include <Illumination/LightSources/ISource.hpp>

#include <memory>
#include <vector>
#include <unordered_set>

namespace RayTracer
{
    using Objects = std::vector<std::shared_ptr<Math::AFigure>>;
    using Sources = std::vector<std::shared_ptr<ISource>>;

    using ObjectsPtrs = std::unordered_set<const std::shared_ptr<Math::AFigure>*>;
    using SourcesPtrs = std::unordered_set<const std::shared_ptr<ISource>*>;

    struct Scene
    {
        Objects objects_;
        Sources lights_;
    };

}

