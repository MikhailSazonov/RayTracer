#pragma once

#include "ISolver.hpp"

#include <Basics/Matrix.hpp>

namespace Math {
    class Linear4x : public ISolver<Operators::Matrix<4, 4>, Operators::Matrix<4, 1>> {
        public:
            static bool hasSolution(const Operators::Matrix<4, 4>&, const Operators::Matrix<4, 1>&);

            static std::optional<std::vector<double>> getSolution(Operators::Matrix<4, 4>, Operators::Matrix<4, 1>);
    };

}

