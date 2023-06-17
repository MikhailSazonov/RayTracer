#pragma once

#include "IFigureFactory.hpp"
#include <Math/Figures/Plane.hpp>
#include <Math/Basics/Point3D.hpp>
#include <Transformers/BaseTransformer.hpp>

//! @brief The factory for the plane
class PlaneFactory : public IFigureFactory
{
public:
    PlaneFactory();
    ~PlaneFactory();

    std::shared_ptr<Math::AFigure> createFigure(const libconfig::Setting &setting) override;
};
