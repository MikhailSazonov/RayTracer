#pragma once

#include <libconfig.h++>
#include <Raytracing/Illumination/LightSources/ISource.hpp>

#include <memory>

class ISourceFactory
{
public:
    virtual ~ISourceFactory() = default;

    /**
     * @brief Light source factory
     *
     * Creates the light as a base pointer from a libconfig setting
     *
     * @param setting The libconfig setting
     * @return The light as a base pointer ISource
     */
    virtual std::unique_ptr<RayTracer::ISource> createSource(const libconfig::Setting &) = 0;
};
