#include "RotationTransformerX.hpp"

namespace Math::Operators {
    RotationTransformerX::RotationTransformerX(double angle)
        : ATransformer(Matrix<4, 4>
        {
            {1,             0,                              0,                          0},
            {0,             cos(angle / 180 * M_PI),        sin(angle / 180 * M_PI),    0},
            {0,             -sin(angle / 180 * M_PI),       cos(angle / 180 * M_PI),    0},
            {0,             0,                              0,                          1},
        }
        )
        {
            setInvOperator({angle});
        }

    void RotationTransformerX::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {1,             0,                                  0,                              0},
            {0,             cos(-args[0] / 180 * M_PI),         sin(-args[0] / 180 * M_PI),     0},
            {0,             -sin(-args[0] / 180 * M_PI),        cos(-args[0] / 180 * M_PI),     0},
            {0,             0,                                  0,                              1},
        };
    }

}
