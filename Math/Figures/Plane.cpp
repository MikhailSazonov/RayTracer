#include "Plane.hpp"

#include <iostream>

namespace Math {
    Plane::Plane(const Point3D& point, const Vector3D& normal, const Operators::ATransformer& transformer,
    size_t color, double specular_coef)
        : AFigure(color, specular_coef, transformer), point_(point), normal_(normal) {}

    std::optional<IntersectParams> Plane::innerNormalWithIntersection(const RayTracer::Ray& ray) {
        double a = this->normal_.dot(ray.direction_);
        double b = this->normal_.dot(ray.source_ - this->point_);

        if (a == 0 || -b / a <= 0)
            return std::nullopt;

        double t = - b / a;

        return IntersectParams(Math::cos(normal_, ray.direction_) < 0 ? normal_ : normal_ * (-1.), ray.at(t));
    }
}
