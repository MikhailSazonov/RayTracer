#include "DirectIllumination.hpp"

namespace RayTracer {

bool DirectIllumination::isShadowed(const Ray& ray,
const Storage::IStorage& storage) {
    if (Settings::isFast()) {
        return false;
    }
    return storage.lookupIntersection(ray).has_value();
}

DirectIllumination::DirectIllumination(const Math::Vector3D& direction, const Math::Vector3D& color,
                                        double diffuse_coef, double specular_coef)
    :   ASource(color), direction_(direction),
        diffuse_coef_(diffuse_coef), specular_coef_(specular_coef) {
        direction_.normalize();
    }

std::optional<Math::Vector3D> DirectIllumination::getColor(const Ray& ray, const Math::Vector3D& normal, double surface_receptivity,
                                                            const Storage::IStorage& storage) {
    double cosin_spec = Math::cos(ray.direction_, direction_);
    double cosin_diffuse = Math::cos(normal, direction_);
    // 1. The direction of ray is bad
    // 2. Shadows
    if ((cosin_spec <= 0 && cosin_diffuse <= 0) || isShadowed(Ray(ray.source_, direction_), storage)) {
        return std::nullopt;
    }
    Math::Vector3D result;
    if (cosin_diffuse > 0) {
        result += color_ * cosin_diffuse * diffuse_coef_;
    }
    if (cosin_spec > 0) {
        result += color_ * pow(cosin_spec, surface_receptivity) * specular_coef_;
    }
    return result;
}

}
