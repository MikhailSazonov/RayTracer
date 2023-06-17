#pragma once

#include "ATransformer.hpp"

namespace Math::Operators
{
    class CustomTransformer : public ATransformer
    {
    public:
        CustomTransformer(const Matrix<4, 4> &);
    };

}

