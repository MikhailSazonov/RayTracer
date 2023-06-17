#pragma once

#include "../ATransformer.hpp"

#include <cmath>

namespace Math::Operators
{
    class RotationTransformerY : public ATransformer
    {
    public:
        RotationTransformerY(double angle);

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}

