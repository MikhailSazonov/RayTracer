#pragma once

#include <fstream>

#include <Basics/Vector3D.hpp>
#include <Basics/Point3D.hpp>

namespace Math {
    struct IntersectParams {
        Vector3D normal;
        Point3D intersection;
        double k;

        inline bool operator==(const IntersectParams& other) const {
            return normal == other.normal && intersection == other.intersection;
        }

        inline bool operator!=(const IntersectParams& other) const {
            return !(*this == other);
        }
    };

    std::ostream& operator<<(std::ostream& stream, const IntersectParams& params);

}
