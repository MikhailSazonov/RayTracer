#include "Ray.hpp"

#include <iostream>

RayTracer::Ray::Ray(const Math::Point3D &source, const Math::Vector3D &direction)
    : source_(source), direction_(direction)
{}

RayTracer::Ray &RayTracer::Ray::ReflectInPlace(const Math::Point3D &intersection, Math::Vector3D normal)
{
    // geometry magic
    direction_ *= -1;
    normal.normalize();
    direction_.normalize();
    double cosa = std::abs(Math::cos(direction_, normal));
    normal *= cosa;

    // reassigning the members
    direction_ = normal * 2. - direction_;

    source_ = intersection;
    return *this;
}

RayTracer::Ray RayTracer::Ray::Reflect(const Math::Point3D &intersection, Math::Vector3D normal)
{
    auto new_ray = *this;
    new_ray.ReflectInPlace(intersection, normal);
    return new_ray;
}

Math::Point3D RayTracer::Ray::at(double t) const
{
    double x = this->source_.x_ + this->direction_.x_ * t;
    double y = this->source_.y_ + this->direction_.y_ * t;
    double z = this->source_.z_ + this->direction_.z_ * t;
    return Math::Point3D(x, y, z);
}
