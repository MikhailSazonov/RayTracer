#pragma once

#include <unordered_map>

#include <Math/Figures/AFigure.hpp>
#include "SphereFactory.hpp"
#include "PlaneFactory.hpp"
#include "CylinderFactory.hpp"
#include "ConeFactory.hpp"

//! @brief The factory for the figures
class FigureFactory
{
private:
    std::unordered_map<std::string, IFigureFactory *> factories_;

public:
    FigureFactory();
    ~FigureFactory();

    std::shared_ptr<Math::AFigure> build(std::string factory, const libconfig::Setting &setting);
};
