#pragma once

#include <Scene.hpp>
#include <Illumination/Ray.hpp>
#include <Storage.hpp>

#include <cmath>

namespace RayTracer
{
    // Helpful struct
    struct RenderingObjectParameters
    {
        Math::IntersectParams params;
        Math::Vector3D color_reaction;
        double specular_coef;
    };

    // Returns the color of pixel,
    // based on the scene
    // Summarizes the light from all the light sources
    Math::Vector3D RayTrace(const Storage::Storage&, Ray &);

    std::optional<RenderingObjectParameters> findClosestObject(const Ray &, const std::vector<std::shared_ptr<Math::AFigure>> &);

    size_t convertToRGB(const Math::Vector3D&);

    bool isOverlap(const Ray&, const std::vector<std::shared_ptr<Math::AFigure>>&);

    void RedistributeTheLights(Math::Vector3D &);
}

