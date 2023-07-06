#pragma once

#include <Basics/Vector3D.hpp>
#include <Illumination/Ray.hpp>
#include <RenderingParams.hpp>

#include <optional>

namespace Storage {
    class IStorage {
        public:
            virtual ~IStorage() = default;

            // Get params of the surface that ray is colliding with
            virtual std::optional<RayTracer::RenderingObjectParameters> lookupIntersection(const RayTracer::Ray&) const = 0;
    };
}
