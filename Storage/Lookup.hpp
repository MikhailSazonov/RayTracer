#pragma once

#include "Scene.hpp"

namespace Storage {
    std::optional<RayTracer::RenderingObjectParameters> findClosestObject(const RayTracer::Ray&,
    const RayTracer::ObjectsPtrs&);
}
