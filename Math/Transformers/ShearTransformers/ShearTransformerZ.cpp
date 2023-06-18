#include "ShearTransformerZ.hpp"

namespace Math::Operators {
    ShearTransformerZ::ShearTransformerZ(double x_shear, double y_shear)
        : ATransformer(Matrix<4, 4>
        {
            {1,             0,          0,          0},
            {0,             1,          0,          0},
            {x_shear,       y_shear,    1,          0},
            {0,             0,          0,          1},
        }, {x_shear, y_shear}
        )
        {}

    void ShearTransformerZ::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {1,             0,              0,          0},
            {0,             1,              0,          0},
            {-args[0],      -args[1],       1,          0},
            {0,             0,              0,          1},
        };
    }

}
