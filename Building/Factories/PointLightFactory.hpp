#pragma once

#include "ISourceFactory.hpp"
#include "Math/Basics/Vector3D.hpp"
#include "Raytracing/Illumination/LightSources/PointLight.hpp"

//! @brief The factory for the point light
class PointLightFactory : public ISourceFactory
{
public:
    PointLightFactory();
    ~PointLightFactory();

    std::unique_ptr<RayTracer::ISource> createSource(const libconfig::Setting &setting) override;
};
