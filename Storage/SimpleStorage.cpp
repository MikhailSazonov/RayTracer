#include <SimpleStorage.hpp>

Storage::SimpleStorage::SimpleStorage(const RayTracer::Scene& scene)
    : IStorage(scene), scene_(scene) {}

Math::Vector3D Storage::SimpleStorage::ProcessRay(RayTracer::Ray& ray) const {
    return RayTrace(scene_.objects_, scene_.lights_, ray);
}
