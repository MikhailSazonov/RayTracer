#include "InfiniteCylinder.hpp"

namespace Math {
    InfiniteCylinder::InfiniteCylinder(const Point3D& center, double radius, const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
        : AFigure(color, specular_coef, transformer), radius_(radius) {
            if (center != Point3D(0., 0., 0.)) {
                *transformer_ *= Operators::TranslationTransformer(center.x_, center.y_, center.z_);
            }
        }

    std::optional<double> InfiniteCylinder::getQuadrFromRay(std::optional<double>& min_k, const RayTracer::Ray& ray) {
        double a = ray.direction_.x_ * ray.direction_.x_ + ray.direction_.z_ * ray.direction_.z_;
        double b = 2 * (ray.direction_.x_ * ray.source_.x_ + ray.direction_.z_ * ray.source_.z_);
        double c = ray.source_.x_ * ray.source_.x_ + ray.source_.z_ * ray.source_.z_ - radius_ * radius_;
        auto k_val = Quadr::getSolution(a, b, c);
        if (!k_val.has_value()) {
            return std::nullopt;
        }
        double k = std::min((*k_val)[0], (*k_val)[1]);
        if (k < 1e-9) {
            k = std::max((*k_val)[0], (*k_val)[1]);
        }
        if (k < 1e-9 || (min_k.has_value() && k >= *min_k)) {
            return std::nullopt;
        }
        return k;
    }

    std::optional<IntersectParams> InfiniteCylinder::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        std::optional<double> min_k = std::nullopt;
        IntersectParams params;
        auto k_opt = getQuadrFromRay(min_k, ray);
        if (k_opt.has_value()) {
            auto y = ray.source_.y_ + ray.direction_.y_ * (*k_opt);
            min_k = *k_opt;
            auto at = ray.at(*k_opt);
            params.intersection = at;
            params.normal = Vector3D(at.x_, 0, at.z_);
        }
        if (min_k.has_value()) {
            return params;
        }
        return std::nullopt;
    }
}
