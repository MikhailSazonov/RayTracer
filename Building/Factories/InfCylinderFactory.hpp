#pragma once

#include "IFigureFactory.hpp"
#include <Math/Figures/InfiniteCylinder.hpp>
#include <Math/Basics/Point3D.hpp>
#include <Transformers/BaseTransformer.hpp>

#include <optional>

//! @brief The factory for the cylinder
class InfCylinderFactory : public IFigureFactory
{
public:
    InfCylinderFactory();
    ~InfCylinderFactory();

    std::shared_ptr<Math::AFigure> createFigure(const libconfig::Setting &setting) override;
};
