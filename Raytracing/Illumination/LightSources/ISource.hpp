#pragma once

#include <optional>
#include <vector>

#include <Illumination/Ray.hpp>
#include <Figures/AFigure.hpp>

#include <IStorage.hpp>

namespace RayTracer
{
    class ISource
    {
    public:
        virtual ~ISource() = default;

        // get the color if the ray hits the source
        virtual std::optional<Math::Vector3D> getColor(const Ray &, const Math::Vector3D &, double,
                                                       const Storage::IStorage&) = 0;
    };

}
