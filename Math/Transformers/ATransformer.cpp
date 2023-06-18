#include "ATransformer.hpp"

Math::Operators::ATransformer::ATransformer(const Math::Operators::Matrix<4, 4>& op, const std::vector<double>& inv_args)
    : operator_(op) {
        setInvOperator(inv_args);
    }

void Math::Operators::ATransformer::setInvOperator(const std::vector<double>&) {
    std::optional<std::vector<double>> inv = Math::MatrixInv::getSolution(operator_);
    if (!inv.has_value()) {
        throw std::runtime_error("Transformation matrix should not be degenerate.");
    }
    inv_operator_ = Matrix<4, 4>{
        {(*inv)[0], (*inv)[4], (*inv)[8], (*inv)[12]},
        {(*inv)[1], (*inv)[5], (*inv)[9], (*inv)[13]},
        {(*inv)[2], (*inv)[6], (*inv)[10], (*inv)[14]},
        {(*inv)[3], (*inv)[7], (*inv)[11], (*inv)[15]}
    };
}

Math::Operators::ATransformer& Math::Operators::ATransformer::operator*=(const Math::Operators::ATransformer& next) {
    operator_ = next.operator_ * operator_;
    inv_operator_ = inv_operator_ * next.inv_operator_;
    return *this;
}
