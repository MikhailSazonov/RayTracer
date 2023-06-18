#include <stdexcept>

#include "FigureFactory.hpp"

FigureFactory::FigureFactory()
{
    this->factories_["spheres"] = std::make_unique<SphereFactory>();
    this->factories_["planes"] = std::make_unique<PlaneFactory>();
    this->factories_["cylinders"] = std::make_unique<CylinderFactory>();
    this->factories_["cones"] = std::make_unique<ConeFactory>();
    this->factories_["inf_cylinders"] = std::make_unique<InfCylinderFactory>();
    this->factories_["inf_cones"] = std::make_unique<InfConeFactory>();
}

std::shared_ptr<Math::AFigure> FigureFactory::build(std::string factory, const libconfig::Setting& setting)
{
    if (this->factories_.find(factory) == this->factories_.end())
        throw std::runtime_error("Factory is not registered.");
    return this->factories_.at(factory)->createFigure(setting);
}
