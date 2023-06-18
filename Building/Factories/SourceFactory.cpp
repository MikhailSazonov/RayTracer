#include <stdexcept>

#include "SourceFactory.hpp"

SourceFactory::SourceFactory()
{
    this->factories_["directional"] = new DirectFactory();
    this->factories_["ambient"] = new AmbiantLightFactory();
    this->factories_["point"] = new PointLightFactory();
}

SourceFactory::~SourceFactory()
{
    for (const auto &factory : this->factories_)
    {
        delete factory.second;
    }
}

std::unique_ptr<RayTracer::ISource> SourceFactory::build(std::string factory, const libconfig::Setting &setting)
{
    if (this->factories_.find(factory) == this->factories_.end())
        throw std::runtime_error("Factory is not registered.");
    return this->factories_.at(factory)->createSource(setting);
}
