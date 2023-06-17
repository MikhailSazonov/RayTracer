#pragma once

#include "../ATransformer.hpp"

#include <cmath>

namespace Math::Operators
{
    class ShearTransformerZ : public ATransformer
    {
    public:
        ShearTransformerZ(double, double);

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}
