#include <Illumination/Ray.hpp>
#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include "../../test_utils.hpp"

#include <iostream>

using namespace RayTracer;
using namespace Math;

int main() {
    std::cout << "RAY\n";
    test([](){
        // SIMPLE
        Ray ray(Point3D(-1, 1, 0), Vector3D(1, -1, 0));
        ray.ReflectInPlace(Point3D(0, 0, 0), Vector3D(0, 1, 0));
        assert_equal(ray.source_, Point3D(0, 0, 0));
        assert_equal(ray.direction_, Vector3D(1, 1, 0));
    }, "Simple");
    test([](){
        // STILL SIMPLE
        Ray ray(Point3D(-10, 5, 0), Vector3D(1, -1, 0));
        ray.ReflectInPlace(Point3D(-7, 2, 0), Vector3D(0, 1, 0));
        assert_equal(ray.source_, Point3D(-7, 2, 0));
        assert_equal(ray.direction_, Vector3D(1, 1, 0));
    }, "In the middle of nowhere");
    test([](){
        // HARDER
        Ray ray(Point3D(-1, 1, 0), Vector3D(1, -1, 0));
        Ray ray2(ray.source_, ray.direction_);
        ray.ReflectInPlace(Point3D(0, 0, 0), Vector3D(0, 1, 0));
        ray.ReflectInPlace(Point3D(1, 1, 0), Vector3D(-1, 0, 0));
        ray.ReflectInPlace(Point3D(0, 2, 0), Vector3D(0, -1, 0));
        ray.ReflectInPlace(Point3D(-1, 1, 0), Vector3D(1, 0, 0));
        assert_equal(ray.source_, ray2.source_);
        assert_equal(ray.direction_, ray2.direction_);
    }, "Bounce");
    std::cout << "Tests passed!\n\n";
}
