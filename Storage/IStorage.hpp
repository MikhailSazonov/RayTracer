#pragma once

#include "Scene.hpp"
#include <Basics/Vector3D.hpp>
#include <Illumination/Ray.hpp>

namespace Storage {
    class IStorage {
        public:
            // Force to implement a constructor with const Raytracer::Scene&
            IStorage(const RayTracer::Scene&) {}

            virtual ~IStorage() = default;

            // Get objects that the ray could collide with
            virtual const RayTracer::Objects& possibleIntersected(const RayTracer::Ray&) const = 0;

            // Get light sources that could affect the pixel
            virtual const RayTracer::Sources& possibleIlluminated(const RayTracer::Ray&) const = 0;
    };
}
