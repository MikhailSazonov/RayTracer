#include "AmbientIllumination.hpp"

namespace RayTracer {

AmbientIllumination::AmbientIllumination(const Math::Vector3D& color)
    : ASource(color) {}

std::optional<Math::Vector3D> AmbientIllumination::getColor(const Ray&, const Math::Vector3D&, double,
                                                            const Storage::IStorage&) {
    return color_;
}

}