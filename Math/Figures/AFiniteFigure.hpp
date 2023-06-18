#pragma once

#include "AFigure.hpp"

#include <Figures/AlgorithmsTools/Box.hpp>

namespace Math {
    class AFiniteFigure : public AFigure {
        protected:
            AFiniteFigure(size_t color, double specular_coef,
            const Operators::ATransformer &transformer) {
                MakeABox();
            }

        private:
            // Makes a parallelepiped (see Box.hpp), in which
            // we can inscribe this figure
            virtual void MakeABox() = 0;

        public:
            const Box& getBox() {
                return box_;
            }

        private:
            Box box_;
    };
}
