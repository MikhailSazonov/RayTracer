#pragma once

#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>

// In fact, it is rectangle parallelepiped, the name is too long

namespace Math {
    namespace Detail {
        enum Length : uint8_t {
            LIMITED, UNLIMITED
        };
    }

    // Vector3D, possibly with inf length
    // Vector with inf length considered as inf in both directions (i.e. line, not ray)
    struct PerfectVector3D {
        Vector3D direction_;
        Detail::Length limit_;
    };

    struct Box {
        // point with minimum in every coordinate (x, y, z)
        Point3D basement_point_;
        PerfectVector3D z_vect_;
        PerfectVector3D y_vect_;
        PerfectVector3D x_vect_;
    };
}
