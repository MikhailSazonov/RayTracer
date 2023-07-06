#include <SimpleStorage.hpp>

Storage::SimpleStorage::SimpleStorage(const RayTracer::Scene& scene) {
    for (auto& obj : scene.objects_) {
        objs_ptrs.insert(&obj);
    }
}

std::optional<RayTracer::RenderingObjectParameters> Storage::SimpleStorage::lookupIntersection(const RayTracer::Ray& ray) const {
    return findClosestObject(ray, objs_ptrs);
}
