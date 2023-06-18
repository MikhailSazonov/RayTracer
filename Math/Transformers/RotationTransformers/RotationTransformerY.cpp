#include "RotationTransformerY.hpp"

namespace Math::Operators {
    RotationTransformerY::RotationTransformerY(double angle)
        : ATransformer(Matrix<4, 4>
        {
            {cos(angle / 180 * M_PI),       0,              sin(angle / 180 * M_PI),    0},
            {0,                             1,              0,                          0},
            {-sin(angle / 180 * M_PI),      0,              cos(angle / 180 * M_PI),    0},
            {0,                             0,              0,                          1},
        }, {angle}
        )
        {}

    void RotationTransformerY::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {cos(-args[0] / 180 * M_PI),        0,              sin(-args[0] / 180 * M_PI),     0},
            {0,                                 1,              0,                              0},
            {-sin(-args[0] / 180 * M_PI),       0,              cos(-args[0] / 180 * M_PI),     0},
            {0,                                 0,              0,                              1},
        };
    }

}
