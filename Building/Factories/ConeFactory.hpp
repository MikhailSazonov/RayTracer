#pragma once

#include "IFigureFactory.hpp"
#include <Math/Figures/Cone.hpp>
#include <Math/Basics/Point3D.hpp>
#include <Transformers/BaseTransformer.hpp>

#include <optional>

//! @brief The factory for the cone
class ConeFactory : public IFigureFactory
{
public:
    ConeFactory();
    ~ConeFactory();

    std::shared_ptr<Math::AFigure> createFigure(const libconfig::Setting &setting) override;
};
