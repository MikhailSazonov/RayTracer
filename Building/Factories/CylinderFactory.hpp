#pragma once

#include "IFigureFactory.hpp"
#include <Math/Figures/Cylinder.hpp>
#include <Math/Basics/Point3D.hpp>
#include <Transformers/BaseTransformer.hpp>

#include <optional>

//! @brief The factory for the cylinder
class CylinderFactory : public IFigureFactory
{
public:
    CylinderFactory();
    ~CylinderFactory();

    std::shared_ptr<Math::AFigure> createFigure(const libconfig::Setting &setting) override;
};
