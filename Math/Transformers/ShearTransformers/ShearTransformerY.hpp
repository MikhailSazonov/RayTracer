#pragma once

#include "../ATransformer.hpp"

#include <cmath>

namespace Math::Operators
{
    class ShearTransformerY : public ATransformer
    {
    public:
        ShearTransformerY(double, double);

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}
