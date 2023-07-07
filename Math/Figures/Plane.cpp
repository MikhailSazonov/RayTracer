#include "Plane.hpp"

#include <iostream>

namespace Math {
    Plane::Plane(const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
        : AFigure(color, specular_coef, transformer) {}

    std::optional<IntersectParams> Plane::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        double a = normal_.dot(ray.direction_);
        double b = normal_.dot(ray.source_);

        if (a == 0 || -b / a <= 0)
            return std::nullopt;

        double t = - b / a;

        return IntersectParams(Math::cos(normal_, ray.direction_) < 0 ? normal_ : normal_ * (-1.), ray.at(t), t);
    }

    void Plane::MakeBox() {
        box_.basement_point_ = transformer_->getOp() * Point3D(0, 0, 0);
        box_.z_vect_ = {transformer_->getOp() * Vector3D(0, 0, 1), Detail::Length::UNLIMITED};
        box_.y_vect_ = {transformer_->getOp() * Vector3D(0, 0, 0), Detail::Length::LIMITED};
        box_.x_vect_ = {transformer_->getOp() * Vector3D(1, 0, 0), Detail::Length::UNLIMITED};
    }
}
