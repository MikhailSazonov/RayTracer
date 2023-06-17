#pragma once

#include "../ATransformer.hpp"

#include <cmath>

namespace Math::Operators
{
    class RotationTransformerZ : public ATransformer
    {
    public:
        RotationTransformerZ(double angle);

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}

