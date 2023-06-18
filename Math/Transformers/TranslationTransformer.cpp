#include "TranslationTransformer.hpp"

namespace Math::Operators {
    TranslationTransformer::TranslationTransformer(double x, double y, double z)
        : ATransformer(Matrix<4, 4>
        {
            {1,             0,              0,              x},
            {0,             1,              0,              y},
            {0,             0,              1,              z},
            {0,             0,              0,              1},
        }, {x, y, z}
        )
        {}

    void TranslationTransformer::setInvOperator(const std::vector<double>& args) {
        inv_operator_ = Matrix<4, 4>
        {
            {1,             0,              0,          -args[0]},
            {0,             1,              0,          -args[1]},
            {0,             0,              1,          -args[2]},
            {0,             0,              0,                 1},
        };
    }

}
