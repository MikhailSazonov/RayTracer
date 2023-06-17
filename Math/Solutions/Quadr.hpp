#pragma once

#include "ISolver.hpp"

namespace Math
{

    class Quadr : public ISolver<double, double, double>
    {
    public:
        static bool hasSolution(double, double, double);

        static std::optional<std::vector<double>> getSolution(double, double, double);
    };

}

