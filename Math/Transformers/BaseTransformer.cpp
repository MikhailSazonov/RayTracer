#include "BaseTransformer.hpp"

Math::Operators::BaseTransformer::BaseTransformer()
    : ATransformer(Math::Operators::Id<4>(), {}) {}

void Math::Operators::BaseTransformer::setInvOperator(const std::vector<double>&) {
    inv_operator_ = Math::Operators::Id<4>();
}
