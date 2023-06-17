#include <Illumination/Ray.hpp>
#include <Illumination/LightSources/DirectIllumination.hpp>
#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include "../../test_utils.hpp"

#include <iostream>

using namespace RayTracer;
using namespace Math;

// Under construction.

int main() {
    std::cout << "DIRECT ILLUMINATION\n";
    test([](){
        // SIMPLE
        DirectIllumination lumus(Vector3D(1., 1., 0.));
        Ray ray(Point3D(0., 0., 0.), Vector3D(1., 1., 0.));
        auto result = lumus.getColor(ray);
        assert(result.has_value());
        assert(std::abs(result->x_ - 255.) < 1e9);
        assert(std::abs(result->y_ - 255.) < 1e9);
        assert(std::abs(result->z_ - 255.) < 1e9);
    }, "Simple");
    test([](){
        DirectIllumination lumus(Vector3D(1., 1., 0.));
        Ray ray(Point3D(0., 0., 0.), Vector3D(1., 0., 0.));
        auto result_color = lumus.getColor(ray);
        assert(result_color.has_value());
        assert(result_color->x_ < 200.);
        assert(result_color->y_ < 200.);
        assert(result_color->z_ < 200.);
    }, "Skew ray");
    test([](){
        DirectIllumination lumus(Vector3D(1., 1., 0.));
        Ray ray(Point3D(0., 0., 0.), Vector3D(1., -0.8, 0.));
        auto result_color = lumus.getColor(ray);
        assert(result_color.has_value());
        assert(result_color->x_ < 50.);
        assert(result_color->y_ < 50.);
        assert(result_color->z_ < 50.);
    }, "Dark");
    test([](){
        DirectIllumination lumus(Vector3D(1., 1., 0.));
        Ray ray(Point3D(0., 0., 0.), Vector3D(1., -1., 0.));
        assert(lumus.getColor(ray) == std::nullopt);
    }, "Orthogonal");
    test([](){
        DirectIllumination lumus(Vector3D(1., 1., 0.));
        Ray ray(Point3D(0., 0., 0.), Vector3D(1., -2., 0.));
        assert(lumus.getColor(ray) == std::nullopt);
    }, "Cosin < 0");
    std::cout << "Tests passed!\n\n";
}
