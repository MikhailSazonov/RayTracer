#pragma once

#include "ATransformer.hpp"

#include <cmath>

namespace Math::Operators
{
    class ScalingTransformer : public ATransformer
    {
    public:
        ScalingTransformer(double multiplicator_x = 1.,
                           double multiplicator_y = 1.,
                           double multiplicator_z = 1.);

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}
