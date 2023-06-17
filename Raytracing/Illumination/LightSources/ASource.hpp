#pragma once

#include "ISource.hpp"

#include <Basics/Vector3D.hpp>

namespace RayTracer
{

    class ASource : public ISource
    {
    protected:
        ASource(const Math::Vector3D &color)
            : color_(color) {}

    protected:
        Math::Vector3D color_;
    };

}

