#include "Lookup.hpp"

std::optional<RayTracer::RenderingObjectParameters> Storage::findClosestObject(const RayTracer::Ray& ray,
const RayTracer::ObjectsPtrs& objects) {
    double min_distance = std::numeric_limits<double>::infinity();
    std::optional<RayTracer::RenderingObjectParameters> closest_object_params = std::nullopt;
    // Scanning for the object that we could collide with.
    // The closest object wins
    for (auto* object : objects) {
        // if the ray was reflected, and we meet another object, put shadow
        // or if the ray was reflected and there are no light sources on the way
        auto intersect_params = (*object)->normalWithIntersection(ray);
        if (intersect_params != std::nullopt) {
            double distance = (intersect_params->intersection - ray.source_).length();
            if (distance < min_distance && distance > 1e-9) {
                min_distance = distance;
                closest_object_params = {*intersect_params,
                                        (*object)->getColorReaction(),
                                        (*object)->getSpecularCoef()};
            }
        }
    }
    return closest_object_params;
}
