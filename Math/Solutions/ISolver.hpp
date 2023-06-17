#pragma once

#include <optional>
#include <vector>
#include <cmath>

namespace Math
{

    template <typename... Args>
    class ISolver
    {
    public:
        virtual ~ISolver() = default;

        static bool hasSolution(Args &&...args);

        static std::optional<std::vector<double>> getSolution(Args &&...args);
    };

}

