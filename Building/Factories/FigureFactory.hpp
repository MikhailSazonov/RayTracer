#pragma once

#include <unordered_map>

#include <Math/Figures/AFigure.hpp>
#include "SphereFactory.hpp"
#include "PlaneFactory.hpp"
#include "CylinderFactory.hpp"
#include "ConeFactory.hpp"
#include "InfCylinderFactory.hpp"
#include "InfConeFactory.hpp"

#include <memory>

//! @brief The factory for the figures
class FigureFactory
{
private:
    std::unordered_map<std::string, std::unique_ptr<IFigureFactory>> factories_;

public:
    FigureFactory();

    std::shared_ptr<Math::AFigure> build(std::string factory, const libconfig::Setting &setting);
};
