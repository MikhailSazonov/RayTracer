#include "ScalingTransformer.hpp"

namespace Math::Operators {
    ScalingTransformer::ScalingTransformer(double multiplicator_x,
                                            double multiplicator_y,
                                            double multiplicator_z)
        : ATransformer(Matrix<4, 4>
        {
            {multiplicator_x,   0,                  0,                  0},
            {0,                 multiplicator_y,    0,                  0},
            {0,                 0,                  multiplicator_z,    0},
            {0,                 0,                  0,                  1},
        }, {multiplicator_x, multiplicator_y, multiplicator_z}
        )
        {}

    void ScalingTransformer::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {1 / args[0],       0,                  0,                  0},
            {0,                 1 / args[1],        0,                  0},
            {0,                 0,                  1 / args[2],        0},
            {0,                 0,                  0,                  1},
        };
    }

}
