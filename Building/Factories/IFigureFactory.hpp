#pragma once

#include <libconfig.h++>
#include <Math/Figures/AFigure.hpp>

#include <Building/TransformerParser/TransformerParser.hpp>

#include <memory>

//! @brief The interface for the figure factory
class IFigureFactory
{
public:
    virtual ~IFigureFactory() = default;

    /**
     * @brief Create a figure base pointer
     *
     * Creates a figure as a base pointer from a libconfig setting
     *
     * @param setting The libconfig setting
     * @return The figure as a base pointer AFigure
     */

    virtual std::shared_ptr<Math::AFigure> createFigure(const libconfig::Setting &) = 0;
};
