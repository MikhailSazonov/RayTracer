#pragma once

#include "../ATransformer.hpp"

#include <cmath>

namespace Math::Operators
{
    class RotationTransformerX : public ATransformer
    {
    public:
        RotationTransformerX(double angle);

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}

