#include "TransformerParser.hpp"

#include <iostream>

Math::Operators::BaseTransformer TransformerParser::getTransformer(const libconfig::Setting& setting) {
    Math::Operators::BaseTransformer transformer;

    if (!setting.exists("transform")) {
        return transformer;
    }

    auto& transform = setting.lookup("transform");

    if (transform.exists("custom")) {
        const libconfig::Setting &custom = transform.lookup("custom");
        auto& matrix = custom["matrix"];

        Math::Operators::Matrix<4, 4> mat;
        for (size_t i = 0; i < 4; ++i) {
            for (size_t j = 0; j < 4; ++j) {
                mat[i][j] = matrix[i][j];
            }
        }
        transformer *= Math::Operators::CustomTransformer(mat);
    }

    if (transform.exists("rotation")) {
        const libconfig::Setting &rotation = transform.lookup("rotation");
        double x = 0., y = 0., z = 0.;
        rotation.lookupValue("x", x);
        rotation.lookupValue("y", y);
        rotation.lookupValue("z", z);
        if (x != 0.) {
            transformer *= Math::Operators::RotationTransformerX(x);
        }
        if (y != 0.) {
            transformer *= Math::Operators::RotationTransformerY(y);
        }
        if (z != 0.) {
            transformer *= Math::Operators::RotationTransformerZ(z);
        }
    }

    if (transform.exists("shear")) {
        const libconfig::Setting &shear = transform.lookup("shear");
        if (shear.exists("x")) {
            const libconfig::Setting &shear_x = shear.lookup("x");
            double y = 0., z = 0.;
            shear_x.lookupValue("y", y);
            shear_x.lookupValue("z", z);
            if (y != 0. || z != 0.) {
                transformer *= Math::Operators::ShearTransformerX(y, z);
            }
        }
        if (shear.exists("y")) {
            const libconfig::Setting &shear_y = shear.lookup("y");
            double x = 0., z = 0.;
            shear_y.lookupValue("x", x);
            shear_y.lookupValue("z", z);
            if (x != 0. || z != 0.) {
                transformer *= Math::Operators::ShearTransformerY(x, z);
            }
        }
        if (shear.exists("z")) {
            const libconfig::Setting &shear_z = shear.lookup("z");
            double x = 0., y = 0.;
            shear_z.lookupValue("x", x);
            shear_z.lookupValue("y", y);
            if (x != 0. || y != 0.) {
                transformer *= Math::Operators::ShearTransformerZ(x, y);
            }
        }
    }

    if (transform.exists("scaling")) {
        const libconfig::Setting &scaling = transform.lookup("scaling");
        double x = 1., y = 1., z = 1.;
        scaling.lookupValue("x", x);
        scaling.lookupValue("y", y);
        scaling.lookupValue("z", z);
        if (x != 1. || y != 1. || z != 1.) {
            transformer *= Math::Operators::ScalingTransformer(x, y, z);
        }
    }

    if (transform.exists("translation")) {
        const libconfig::Setting &translation = transform.lookup("translation");
        double x = 0., y = 0., z = 0.;
        translation.lookupValue("x", x);
        translation.lookupValue("y", y);
        translation.lookupValue("z", z);
        if (x != 0. || y != 0. || z != 0.) {
            transformer *= Math::Operators::TranslationTransformer(x, y, z);
        }
    }
    return transformer;
}
