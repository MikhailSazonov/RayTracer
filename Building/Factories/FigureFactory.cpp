#include <stdexcept>

#include "FigureFactory.hpp"

FigureFactory::FigureFactory()
{
    this->factories_["spheres"] = new SphereFactory();
    this->factories_["planes"] = new PlaneFactory();
    this->factories_["cylinders"] = new CylinderFactory();
    this->factories_["cones"] = new ConeFactory();
}

FigureFactory::~FigureFactory()
{
    for (const auto &factory : this->factories_)
    {
        delete factory.second;
    }
}

std::shared_ptr<Math::AFigure> FigureFactory::build(std::string factory, const libconfig::Setting& setting)
{
    if (this->factories_.find(factory) == this->factories_.end())
        throw std::runtime_error("Factory is not registered.");
    return this->factories_.at(factory)->createFigure(setting);
}
