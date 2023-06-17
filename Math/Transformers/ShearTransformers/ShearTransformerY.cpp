#include "ShearTransformerY.hpp"

namespace Math::Operators {
    ShearTransformerY::ShearTransformerY(double x_shear, double z_shear)
        : ATransformer(Matrix<4, 4>
        {
            {1,             0,          0,          0},
            {x_shear,       1,          z_shear,    0},
            {0,             0,          1,          0},
            {0,             0,          0,          1},
        }
        )
        {
            setInvOperator({x_shear, z_shear});
        }

    void ShearTransformerY::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {1,             0,          0,          0},
            {-args[0],      1,          -args[1],   0},
            {0,             0,          1,          0},
            {0,             0,          0,          1},
        };
    }

}
