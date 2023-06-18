#pragma once

#include "IFigureFactory.hpp"
#include <Math/Figures/InfiniteCone.hpp>
#include <Math/Basics/Point3D.hpp>
#include <Transformers/BaseTransformer.hpp>

#include <optional>

//! @brief The factory for the cone
class InfConeFactory : public IFigureFactory
{
public:
    InfConeFactory();
    ~InfConeFactory();

    std::shared_ptr<Math::AFigure> createFigure(const libconfig::Setting &setting) override;
};
