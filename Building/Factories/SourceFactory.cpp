#include <stdexcept>

#include "SourceFactory.hpp"

SourceFactory::SourceFactory()
{
    this->factories_["directional"] = std::make_unique<DirectFactory>();
    this->factories_["ambient"] = std::make_unique<AmbiantLightFactory>();
    this->factories_["point"] = std::make_unique<PointLightFactory>();
}

std::unique_ptr<RayTracer::ISource> SourceFactory::build(std::string factory, const libconfig::Setting &setting)
{
    if (this->factories_.find(factory) == this->factories_.end())
        throw std::runtime_error("Factory is not registered.");
    return this->factories_.at(factory)->createSource(setting);
}
