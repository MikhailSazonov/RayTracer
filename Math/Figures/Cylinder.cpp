#include "Cylinder.hpp"

namespace Math {
    Cylinder::Cylinder(const Point3D& center, double radius, double height, const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
        : AFigure(color, specular_coef, transformer), radius_(radius), height_(height) {
            if (center != Point3D(0., 0., 0.)) {
                *transformer_ *= Operators::TranslationTransformer(center.x_, center.y_, center.z_);
            }
        }

    std::optional<double> Cylinder::getQuadrFromRay(std::optional<double>& min_k, const RayTracer::Ray& ray) {
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

    void Cylinder::CheckPlaneIntersect(std::optional<double>& min_k, IntersectParams& params,
    const RayTracer::Ray& ray, double y_value, double sign) {
        double k;
        if (ray.direction_.y_ != 0) {
            k = (y_value - ray.source_.y_) / ray.direction_.y_;
            if (k < 0 || (min_k.has_value() && k >= *min_k)) {
                return;
            }
            auto x = ray.source_.x_ + ray.direction_.x_ * k;
            auto z = ray.source_.z_ + ray.direction_.z_ * k;
            if (x * x + z * z > radius_ * radius_) {
                return;
            }
        } else {
            if (std::abs(ray.source_.y_ - y_value) >= 1e-9) {
                return;
            }
            auto k_opt = getQuadrFromRay(min_k, ray);
            if (!k_opt.has_value()) {
                return;
            }
            k = *k_opt;
        }
        min_k = k;
        params.intersection = ray.at(k);
        params.normal = Vector3D(0, 1, 0) * sign;
    }

    std::optional<IntersectParams> Cylinder::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        std::optional<double> min_k = std::nullopt;
        IntersectParams params;
        // Check for bottom intersection
        CheckPlaneIntersect(min_k, params, ray, -height_, -1);
        // Check for upper intersection
        CheckPlaneIntersect(min_k, params, ray, 0, 1);
        // Other intersections
        auto k_opt = getQuadrFromRay(min_k, ray);
        if (k_opt.has_value()) {
            auto y = ray.source_.y_ + ray.direction_.y_ * (*k_opt);
            if (y < 0 && y > -height_) {
                min_k = *k_opt;
                auto at = ray.at(*k_opt);
                params.intersection = at;
                params.normal = Vector3D(at.x_, 0, at.z_);
            }
        }
        if (min_k.has_value()) {
            return params;
        }
        return std::nullopt;
    }

    void Cylinder::MakeABox() {
        box_.point_000_ = Point3D(-radius, -height, -radius);
        box_.point_001_ = Point3D(radius, -height, -radius);
        box_.point_010_ = Point3D(-radius, 0, -radius);
        box_.point_100_ = Point3D(-radius, -height, radius);

        box_.point_000_ *= transformer_.getOp();
        box_.point_001_ *= transformer_.getOp();
        box_.point_010_ *= transformer_.getOp();
        box_.point_100_ *= transformer_.getOp();
    }
}
