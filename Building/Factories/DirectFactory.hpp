#pragma once

#include "ISourceFactory.hpp"
#include <Math/Basics/Vector3D.hpp>
#include <Raytracing/Illumination/LightSources/DirectIllumination.hpp>
// #include <Math/Figures/Plane.hpp>
// #include <Transformers/BaseTransformer.hpp>

//! @brief The factory for the direct light
class DirectFactory : public ISourceFactory
{
public:
    DirectFactory();
    ~DirectFactory();

    std::unique_ptr<RayTracer::ISource> createSource(const libconfig::Setting &setting) override;
};
