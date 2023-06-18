#include "Plane.hpp"

#include <iostream>

namespace Math {
    Plane::Plane(const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
        : AFigure(color, specular_coef, transformer) {
            point_ = Point3D(0, 0, 0) * transformer_.getOp();
            normal_ = Vector3D(0, 1, 0) * transformer_.getOp();
        }

    std::optional<IntersectParams> Plane::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        double a = this->normal_.dot(ray.direction_);
        double b = this->normal_.dot(ray.source_ - this->point_);

        if (a == 0 || -b / a <= 0)
            return std::nullopt;

        double t = - b / a;

        return IntersectParams(Math::cos(normal_, ray.direction_) < 0 ? normal_ : normal_ * (-1.), ray.at(t));
    }

    void MakeBox() override {
        box_.basement_point_ = point_;
        box_.z_vect_ = {Vector3D(0, 0, 1), Detail::Length::UNLIMITED} * transformer_.getOp();
        box_.y_vect_ = {Vector3D(0, 0, 0), Detail::Length::LIMITED} * transformer_.getOp();
        box_.x_vect_ = {Vector3D(1, 0, 0), Detail::Length::UNLIMITED} * transformer_.getOp();
    }
}
