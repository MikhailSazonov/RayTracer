#pragma once

#include <Illumination/Ray.hpp>
#include <Basics/Vector3D.hpp>

#include "Params/IntersectParams.hpp"

#include <optional>

namespace Math {
    class IFigure {
        public:
            virtual ~IFigure() = default;

            // Returns normal vector to the point where ray hits the figure,
            // if the ray hits the figure,
            // std::nullopt otherwise
            // do we need to separate function to get point where hit,
            // and get normal vector?
            virtual std::optional<IntersectParams> normalWithIntersection(const RayTracer::Ray&) = 0;

            // color is provided by the source of light, the surface just provides the
            // property of interaction with the photons:
            // Vector3D (r, g, b),
            // where (r, g, b) \in [0, 1];
            // 0 means that the ray in this spectre is fully absorbed (no emitting of light of this spectre)
            // 1 means that the ray in this spectre is fully reflected (all the light is emitted)
            // in constructor, the actual color is presented, but then the conversion goes
            // (0x00 means full absorbtion, 0xFF - full reflection)
            virtual const Vector3D& getColorReaction() const = 0;

            // Coef for specular light
            // (see the Phong-Blinn reflection model)
            virtual double getSpecularCoef() const = 0;
    };

}

