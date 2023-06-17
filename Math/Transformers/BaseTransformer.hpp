#pragma once

#include "ATransformer.hpp"

namespace Math::Operators
{
    class BaseTransformer : public ATransformer
    {
    public:
        BaseTransformer();

    protected:
        void setInvOperator(const std::vector<double> &);
    };

}

