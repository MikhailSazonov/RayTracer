#include "RotationTransformerZ.hpp"

namespace Math::Operators {
    RotationTransformerZ::RotationTransformerZ(double angle)
        : ATransformer(Matrix<4, 4>
        {
            {cos(angle / 180 * M_PI),       sin(angle / 180 * M_PI),        0,          0},
            {-sin(angle / 180 * M_PI),      cos(angle / 180 * M_PI),        0,          0},
            {0,                             0,                              1,          0},
            {0,                             0,                              0,          1},
        }, {angle}
        )
        {}

    void RotationTransformerZ::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {cos(-args[0] / 180 * M_PI),        sin(-args[0] / 180 * M_PI),         0,          0},
            {-sin(-args[0] / 180 * M_PI),       cos(-args[0] / 180 * M_PI),         0,          0},
            {0,                                 0,                                  1,          0},
            {0,                                 0,                                  0,          1},
        };
    }

}
