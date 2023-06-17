#pragma once

#include "IFigureFactory.hpp"
#include <Math/Figures/Sphere.hpp>
#include <Math/Basics/Point3D.hpp>
#include <Transformers/BaseTransformer.hpp>

//! @brief The factory for the sphere
class SphereFactory : public IFigureFactory
{
public:
    SphereFactory();
    ~SphereFactory();

    std::shared_ptr<Math::AFigure> createFigure(const libconfig::Setting &setting) override;
};
