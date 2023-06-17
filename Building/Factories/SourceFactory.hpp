#pragma once

#include <unordered_map>

#include <Raytracing/Illumination/LightSources/ISource.hpp>
#include "DirectFactory.hpp"
#include "AmbientLight.hpp"
#include "PointLightFactory.hpp"

//! @brief The factory for the factories (main factory)
class SourceFactory
{
private:
    std::unordered_map<std::string, ISourceFactory *> factories_;

public:
    SourceFactory();
    ~SourceFactory();

    /**
     * @brief Build a source from a factory and a setting
     *
     * @param factory The factory name
     *
     * @param setting The setting
     * @return The source as a base pointer
     */
    std::unique_ptr<RayTracer::ISource> build(std::string factory, const libconfig::Setting &setting);
};
