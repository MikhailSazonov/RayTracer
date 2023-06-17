#include "Camera.hpp"

namespace RayTracer {

    Camera::Camera(double fieldOfView,
            const std::pair<size_t, size_t> resolution,
            const Math::Operators::ATransformer& transformer)
        :   origin_(0., 5., 0.),
            screen_(Math::Point3D(-5., 0., 5.), Math::Vector3D(0, 10, 0), Math::Vector3D(10, 0, 0)),
            resolution_(resolution)
        {
            if (fieldOfView >= 180) {
                throw std::runtime_error("Too big field of view.");
            }
            screen_.left_bottom_.z_ = 5 / tan(fieldOfView / 360 * M_PI);
            origin_ = transformer.getOp() * origin_;
            screen_.left_bottom_ = transformer.getOp() * screen_.left_bottom_;
            screen_.left_side_ = transformer.getOp() * screen_.left_side_;
            screen_.bottom_side_ = transformer.getOp() * screen_.bottom_side_;
        }

    Ray Camera::ray(double u, double v) const {
        auto screen_point = screen_.pointAt(u, v);
        return Ray(origin_, screen_point - origin_);
    }

}

