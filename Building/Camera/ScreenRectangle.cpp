#include "ScreenRectangle.hpp"

namespace RayTracer {

ScreenRectangle::ScreenRectangle(const Math::Point3D& left_bottom, const Math::Vector3D& left_side, const Math::Vector3D& bottom_side)
    : left_bottom_(left_bottom), left_side_(left_side), bottom_side_(bottom_side) {}

Math::Point3D ScreenRectangle::pointAt(double u, double v) const {
    return left_bottom_ + bottom_side_ * u + left_side_ * v;
}

}
