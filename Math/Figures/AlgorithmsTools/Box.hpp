#pragma once

#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>

// In fact, it is rectangle parallelepiped, the name is too long

namespace Math {
    struct Box {
        Point3D point_000_;
        Point3D point_001_;
        Point3D point_010_;
        Point3D point_100_;
    };
}
