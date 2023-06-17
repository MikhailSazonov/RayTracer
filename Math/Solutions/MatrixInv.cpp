#include "MatrixInv.hpp"
#include "Linear4x.hpp"

namespace Math {
    std::optional<std::vector<double>> Math::MatrixInv::getSolution(const Operators::Matrix<4, 4>& mat) {
        std::vector<double> ans_mat;
        std::optional<std::vector<double>> next_column;
        Operators::Matrix<4, 1> next_y{0., 0., 0., 0.};
        for (size_t i = 0; i < 4; ++i) {
            next_y[i][0] = 1.;
            if ((next_column = Linear4x::getSolution(mat, next_y)) == std::nullopt) {
                return std::nullopt;
            }
            for (auto j : *next_column) {
                ans_mat.push_back(j);
            }
            next_y[i][0] = 0.;
        }
        return ans_mat;
    }

    bool Math::MatrixInv::hasSolution(const Operators::Matrix<4, 4>& mat) {
        return getSolution(mat).has_value();
    }

}
