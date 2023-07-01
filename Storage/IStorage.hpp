#pragma once

#include "Scene.hpp"
#include <Basics/Vector3D.hpp>
#include <Illumination/Ray.hpp>

namespace Storage {
    class IStorage {
        public:
            // force to implement a constructor with const Raytracer::Scene&
            IStorage(const RayTracer::Scene&) {}

            virtual ~IStorage() = default;

            virtual Math::Vector3D ProcessRay(RayTracer::Ray&) const = 0;
    };
}
