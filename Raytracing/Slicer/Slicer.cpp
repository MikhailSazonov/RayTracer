#include "Slicer.hpp"
#include <cstddef>

// z, x, y are known, z, x, y \in Z+
// need to find such a, b; that x = ka; y = tb, z = ab for some k, t \in Z+
// if solution in Z+ does not exist, we tune z (do z++) until we find the solution
static std::vector<size_t> Solve(size_t x, size_t y, size_t z)
{
    for (; (x * y) % z != 0; ++z);
    size_t d = (x * y) / z;
    std::vector<size_t> result{1, d};
    for (size_t i = 2; i * i <= d; ++i)
    {
        if (d % i == 0 && x % i == 0)
        {
            result[0] = i;
            result[1] = d / i;
        }
    }
    return {x / result[0], y / result[1], z};
}

std::vector<size_t> RayTracer::Slicer::Slice(size_t width, size_t height, size_t workers)
{
    return Solve(width, height, workers);
}
