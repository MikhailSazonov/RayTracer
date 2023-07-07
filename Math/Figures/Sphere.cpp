#include "Sphere.hpp"
#include <Solutions/Quadr.hpp>

namespace Math {
    Sphere::Sphere(const Point3D& center, double radius, const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
        : AFigure(color, specular_coef, transformer), center_(center), radius_(radius) {}

    std::optional<IntersectParams> Sphere::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        double source_x_shift = ray.source_.x_ - center_.x_;
        double source_y_shift = ray.source_.y_ - center_.y_;
        double source_z_shift = ray.source_.z_ - center_.z_;
        double a = ray.direction_.x_ * ray.direction_.x_
                    + ray.direction_.y_ * ray.direction_.y_
                    + ray.direction_.z_ * ray.direction_.z_;
        double b = 2 * (source_x_shift * ray.direction_.x_
                    + source_y_shift * ray.direction_.y_
                    + source_z_shift * ray.direction_.z_);
        double c = source_x_shift * source_x_shift
                    + source_y_shift * source_y_shift
                    + source_z_shift * source_z_shift
                    - radius_ * radius_;
        auto result = Quadr::getSolution(a, b, c);
        if (result == std::nullopt || ((*result)[0] <= 0 && (*result)[1] <= 0)) {
            return std::nullopt;
        }
        if ((*result)[0] >= (*result)[1]) {
            std::swap((*result)[0], (*result)[1]);
        }
        auto root = ((*result)[0] > 0 ? (*result)[0] : (*result)[1]);
        auto intersectionPoint = Point3D(ray.source_.x_ + ray.direction_.x_ * root,
                       ray.source_.y_ + ray.direction_.y_ * root,
                       ray.source_.z_ + ray.direction_.z_ * root);
        return IntersectParams(getNormalVector(intersectionPoint), intersectionPoint, root);
    }

    void Sphere::MakeBox() {
        box_.basement_point_ = center_ - Vector3D(radius_, radius_, radius_);
        box_.z_vect_ = {transformer_->getOp() * Vector3D(0, 0, radius_), Detail::Length::LIMITED};
        box_.y_vect_ = {transformer_->getOp() * Vector3D(0, radius_, 0), Detail::Length::LIMITED};
        box_.x_vect_ = {transformer_->getOp() * Vector3D(radius_, 0, 0), Detail::Length::LIMITED};
    }

}
