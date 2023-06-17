#include "AFigure.hpp"

#include <iostream>

namespace Math {

AFigure::AFigure(size_t color, double specular_coef,
        const Operators::ATransformer& transformer)
            : color_coef_(((color >> 16) & 0xFF) / 255.,
            ((color >> 8) & 0xFF) / 255.,
            (color & 0xFF) / 255.),
            specular_coef_(specular_coef),
            transformer_(std::make_unique<Operators::ATransformer>(transformer))
            {}

std::optional<IntersectParams> AFigure::normalWithIntersection(const RayTracer::Ray& ray) {
    auto ray_tr = ray.coordinatesChange(transformer_->getInvOp());
    auto result = innerNormalWithIntersection(ray_tr);
    if (!result.has_value()) {
        return std::nullopt;
    }
    result->intersection = transformer_->getOp() * result->intersection;
    result->normal = transformer_->getOp() * result->normal;
    return result;
}

}
