#include "Linear4x.hpp"

namespace Math {
    std::optional<std::vector<double>> Math::Linear4x::getSolution(Math::Operators::Matrix<4, 4> A, Math::Operators::Matrix<4, 1> y) {
        // direct elimination
        for (size_t i = 0; i < 4; ++i) {
            // swapping the rows
            if (A[i][i] == 0.) {
                for (size_t j = i + 1; j < 4; ++j) {
                    if (A[j][i] != 0.) {
                        for (size_t k = 0; k < 4; ++k) {
                            std::swap(A[i][k], A[j][k]);
                        }
                        std::swap(y[i][0], y[j][0]);
                        break;
                    }
                    if (j == 3) {
                        return std::nullopt;
                    }
                }
            }
            for (size_t j = i + 1; j < 4; ++j) {
                double numer = A[j][i];
                for (size_t k = i; k < 4; ++k) {
                    A[j][k] -= A[i][k] * numer / A[i][i];
                }
                y[j][0] -= y[i][0] * numer / A[i][i];
            }
        }
        // inverse elimination
        for (int i = 3; i >= 0; --i) {
            // diagonals should be != 0
            if (A[i][i] == 0.) {
                return std::nullopt;
            }
            for (int j = i - 1; j >= 0; --j) {
                y[j][0] -= y[i][0] * A[j][i] / A[i][i];
                A[j][i] = 0.;
            }
        }
        // == 0 is already checked
        return std::vector<double>{y[0][0] / A[0][0], y[1][0] / A[1][1], y[2][0] / A[2][2], y[3][0] / A[3][3]};
    }

    bool Math::Linear4x::hasSolution(const Math::Operators::Matrix<4, 4>& A, const Math::Operators::Matrix<4, 1>& y) {
        return getSolution(A, y).has_value();
    }

}
