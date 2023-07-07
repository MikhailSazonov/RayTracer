#include "Cylinder.hpp"

namespace Math {
    Cylinder::Cylinder(const Point3D& center, double radius, std::optional<double> height, const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
        : AFigure(color, specular_coef, transformer), radius_(radius) {
            if (height.has_value()) {
                height_ = *height;
            } else {
                limited_ = false;
            }
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
        params.k = k;
    }

    std::optional<IntersectParams> Cylinder::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        std::optional<double> min_k = std::nullopt;
        IntersectParams params;
        if (limited_) {
            // Check for bottom intersection
            CheckPlaneIntersect(min_k, params, ray, -height_, -1);
            // Check for upper intersection
            CheckPlaneIntersect(min_k, params, ray, 0, 1);
        }
        // Other intersections
        auto k_opt = getQuadrFromRay(min_k, ray);
        if (k_opt.has_value()) {
            auto y = ray.source_.y_ + ray.direction_.y_ * (*k_opt);
            if (!limited_ || (y < 0 && y > -height_)) {
                min_k = *k_opt;
                auto at = ray.at(*k_opt);
                params.intersection = at;
                params.normal = Vector3D(at.x_, 0, at.z_);
                params.k = *min_k;
            }
        }
        if (min_k.has_value()) {
            return params;
        }
        return std::nullopt;
    }

    void Cylinder::MakeBox() {
        if (limited_) {
            box_.basement_point_ = transformer_->getOp() * Point3D(-radius_, -height_, -radius_);
            box_.z_vect_ = {transformer_->getOp() * Vector3D(0, 0, 2 * radius_), Detail::Length::LIMITED};
            box_.y_vect_ = {transformer_->getOp() * Vector3D(0, height_, 0), Detail::Length::LIMITED};
            box_.x_vect_ = {transformer_->getOp() * Vector3D(2 * radius_, 0, 0), Detail::Length::LIMITED};
        } else {
            box_.basement_point_ = transformer_->getOp() * Point3D(-radius_, -height_, -radius_);
            box_.z_vect_ = {transformer_->getOp() * Vector3D(0, 0, 2 * radius_), Detail::Length::LIMITED};
            box_.y_vect_ = {transformer_->getOp() * Vector3D(0, 1, 0), Detail::Length::UNLIMITED};
            box_.x_vect_ = {transformer_->getOp() * Vector3D(2 * radius_, 0, 0), Detail::Length::LIMITED};
        }
    }
}
