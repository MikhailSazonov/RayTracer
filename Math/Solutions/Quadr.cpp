#include "Quadr.hpp"

namespace Math {

    std::optional<std::vector<double>> Math::Quadr::getSolution(double a, double b, double c) {
        double d = b * b - 4 * a * c;
        if (d < 0) {
            return std::nullopt;
        }
        double sqrt_d = sqrt(d);
        std::vector<double> results;
        // could be the same
        results.push_back((-b + sqrt_d) / (2 * a));
        results.push_back((-b - sqrt_d) / (2 * a));
        return results;
    }

    bool Math::Quadr::hasSolution(double a, double b, double c) {
        return b * b - 4 * a * c >= 0;
    }

}
