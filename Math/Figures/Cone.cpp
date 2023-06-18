#include "Cone.hpp"

#include <iostream>

namespace Math {
    Cone::Cone(const Point3D& center, double radius, std::optional<double> height, const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
    : AFigure(color, specular_coef, transformer), radius_(radius),
    max_y_normal_(radius_ * radius_ / height_) {
        if (height.has_value()) {
            height_ = *height;
        } else {
            limited_ = false;
        }
        if (center != Point3D(0., 0., 0.)) {
            *transformer_ *= Operators::TranslationTransformer(center.x_, center.y_, center.z_);
        }
    }

    std::optional<double> Cone::getQuadrFromRay(std::optional<double>& min_k, const RayTracer::Ray& ray) {
        double a = ray.direction_.x_ * ray.direction_.x_ + ray.direction_.z_ * ray.direction_.z_
                    - ray.direction_.y_ * ray.direction_.y_ * radius_ / height_;
        double b = 2 * (ray.direction_.x_ * ray.source_.x_ + ray.direction_.z_ * ray.source_.z_)
                    - 2 * ray.source_.y_ * ray.direction_.y_ * radius_ / height_;
        double c = ray.source_.x_ * ray.source_.x_ + ray.source_.z_ * ray.source_.z_
                    - ray.source_.y_ * ray.source_.y_ * radius_ / height_;
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

    void Cone::CheckPlaneIntersect(std::optional<double>& min_k, IntersectParams& params,
    const RayTracer::Ray& ray) {
        double k;
        if (ray.direction_.y_ != 0) {
            k = (-height_ - ray.source_.y_) / ray.direction_.y_;
            if (k < 0 || (min_k.has_value() && k >= *min_k)) {
                return;
            }
            auto p = ray.at(k);
            if (p.x_ * p.x_ + p.z_ * p.z_ > p.y_ * p.y_ * radius_ / height_) {
                return;
            }
        } else {
            if (std::abs(-height_ - ray.source_.y_) >= 1e-9) {
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
        params.normal = Vector3D(0, -1, 0);
    }

    std::optional<IntersectParams> Cone::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        std::optional<double> min_k = std::nullopt;
        IntersectParams params;
        if (limited_) {
            // Check for bottom intersection
            CheckPlaneIntersect(min_k, params, ray);
        }
        // Other intersections
        auto k_opt = getQuadrFromRay(min_k, ray);
        if (k_opt.has_value()) {
            auto y = ray.source_.y_ + ray.direction_.y_ * (*k_opt);
            if (!limited_ || (y > -height_ && y < 0)) {
                min_k = *k_opt;
                auto at = ray.at(*k_opt);
                params.intersection = at;
                params.normal = Vector3D(at.x_, max_y_normal_ * (- at.y_ / height_), at.z_);
            }
        }
        if (min_k.has_value()) {
            return params;
        }
        return std::nullopt;
    }

    void Cone::MakeBox() {
        if (limited_) {
            box_.basement_point_ = Point3D(-radius_, -height_, -radius_) * transformer_.getOp();
            box_.z_vect_ = {Vector3D(0, 0, 2 * radius_), Detail::Length::LIMITED} * transformer_.getOp();
            box_.y_vect_ = {Vector3D(0, height_, 0), Detail::Length::LIMITED} * transformer_.getOp();
            box_.x_vect_ = {Vector3D(2 * radius_, 0, 0), Detail::Length::LIMITED} * transformer_.getOp();
        } else {
            box_.basement_point_ = Point3D(0, 0, 0);
            box_.z_vect_ = {Vector3D(0, 0, 1), Detail::Length::UNLIMITED};
            box_.y_vect_ = {Vector3D(0, 1, 0), Detail::Length::UNLIMITED};
            box_.x_vect_ = {Vector3D(1, 0, 0), Detail::Length::UNLIMITED};
        }
    }
}
