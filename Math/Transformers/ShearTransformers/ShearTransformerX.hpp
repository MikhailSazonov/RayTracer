#pragma once

#include "../ATransformer.hpp"

#include <cmath>

namespace Math::Operators
{
    class ShearTransformerX : public ATransformer
    {
    public:
        ShearTransformerX(double, double);

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}
