#pragma once

#include <vector>
#include <cstddef>

namespace RayTracer
{

    class Slicer
    {
    public:
        static std::vector<size_t> Slice(size_t width, size_t height, size_t workers);
    };

}
