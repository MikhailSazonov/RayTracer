#include "ShearTransformerX.hpp"

namespace Math::Operators {
    ShearTransformerX::ShearTransformerX(double y_shear, double z_shear)
        : ATransformer(Matrix<4, 4>
        {
            {1,             y_shear,    z_shear,    0},
            {0,             1,          0,          0},
            {0,             0,          1,          0},
            {0,             0,          0,          1},
        }, {y_shear, z_shear}
        )
        {}

    void ShearTransformerX::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {1,             -args[0],       -args[1],   0},
            {0,             1,              0,          0},
            {0,             0,              1,          0},
            {0,             0,              0,          1},
        };
    }

}
