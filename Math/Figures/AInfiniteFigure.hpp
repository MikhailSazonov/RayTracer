#pragma once

#include "AFigure.hpp"

namespace Math {
    class AInfiniteFigure : public AFigure {
        protected:
            AInfiniteFigure(size_t color, double specular_coef,
            const Operators::ATransformer &transformer);
    };
}
