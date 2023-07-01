#include <SimpleStorage.hpp>

Storage::SimpleStorage::SimpleStorage(const RayTracer::Scene& scene)
    : IStorage(scene), scene_(scene) {}

const RayTracer::Objects& Storage::SimpleStorage::possibleIntersected(const RayTracer::Ray&) const {
    return scene_.objects_;
}

const RayTracer::Sources& Storage::SimpleStorage::possibleIlluminated(const RayTracer::Ray&) const {
    return scene_.lights_;
}
