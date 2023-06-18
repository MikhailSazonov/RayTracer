#pragma once

#include "ISourceFactory.hpp"
#include <Math/Figures/Plane.hpp>
#include <Math/Basics/Point3D.hpp>
#include <Raytracing/Illumination/LightSources/AmbientIllumination.hpp>

//! @brief The factory for the ambient light
class AmbientLightFactory : public ISourceFactory
{
public:
    AmbientLightFactory();
    ~AmbientLightFactory();

    std::unique_ptr<RayTracer::ISource> createSource(const libconfig::Setting &) override;
};