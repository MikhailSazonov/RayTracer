#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include <Figures/Sphere.hpp>
#include "../../test_utils.hpp"

#include <iostream>

using namespace Math;
using namespace RayTracer;

int main() {
    std::cout << "SPHERE\n";
    test([](){
        // SIMPLE
        Sphere sphere(Point3D(0., 0., 0.), 1.);
        {
            Ray ray1(Point3D(2., 0., 0.), Vector3D(-1., 0., 0.));
            Ray ray2(Point3D(2., 0., 0.), Vector3D(-0.05, 0., 0.));
            Ray ray3(Point3D(2., 0., 0.), Vector3D(1, 0., 0.));
            assert(sphere.normalWithIntersection(ray1));
            assert(sphere.normalWithIntersection(ray2));
            assert(!sphere.normalWithIntersection(ray3));
        }
        {
            Ray ray1(Point3D(0., 2., 0.), Vector3D(0., -1., 0.));
            Ray ray2(Point3D(0., 2., 0.), Vector3D(0., -0.05, 0.));
            Ray ray3(Point3D(0., 2., 0.), Vector3D(0., 1., 0.));
            assert(sphere.normalWithIntersection(ray1));
            assert(sphere.normalWithIntersection(ray2));
            assert(!sphere.normalWithIntersection(ray3));
        }
        {
            Ray ray1(Point3D(0., 0., 2.), Vector3D(0., 0., -1.));
            Ray ray2(Point3D(0., 0., 2.), Vector3D(0., 0., -0.05));
            Ray ray3(Point3D(0., 0., 2.), Vector3D(0., 0., 1.));
            assert(sphere.normalWithIntersection(ray1));
            assert(sphere.normalWithIntersection(ray2));
            assert(!sphere.normalWithIntersection(ray3));
        }
        {
            Ray ray1(Point3D(0., 0., -2.), Vector3D(0., 0., 1.));
            Ray ray2(Point3D(0., 0., -2.), Vector3D(0., 0., 0.05));
            Ray ray3(Point3D(0., 0., -2.), Vector3D(0., 0., -1.));
            assert(sphere.normalWithIntersection(ray1));
            assert(sphere.normalWithIntersection(ray2));
            assert(!sphere.normalWithIntersection(ray3));
        }
    }, "Simple");
    test([](){
        // NORMAL
        Sphere sphere(Point3D(0., 0., 0.), 1.);
        {
            Ray ray1(Point3D(2., 0., 0.), Vector3D(-1., 0., 0.));
            Ray ray3(Point3D(2., 0., 0.), Vector3D(1., 0., 0.));
            assert_equal(*sphere.normalWithIntersection(ray1), IntersectParams{Vector3D(1., 0., 0.), Point3D(1., 0., 0.)});
            assert(!sphere.normalWithIntersection(ray3));
        }
        {
            Ray ray1(Point3D(0., 2., 0.), Vector3D(0., -1., 0.));
            Ray ray3(Point3D(0., 2., 0.), Vector3D(0., 1., 0.));
            assert_equal(*sphere.normalWithIntersection(ray1), IntersectParams{Vector3D(0., 1., 0.), Point3D(0., 1., 0.)});
            assert(!sphere.normalWithIntersection(ray3));
        }
        {
            Ray ray1(Point3D(0., 0., 2.), Vector3D(0., 0., -1.));
            Ray ray3(Point3D(0., 0., 2.), Vector3D(0., 0., 1.));
            assert_equal(*sphere.normalWithIntersection(ray1), IntersectParams{Vector3D(0., 0., 1.), Point3D(0., 0., 1.)});
            assert(!sphere.normalWithIntersection(ray3));
        }
        {
            Ray ray1(Point3D(0., 0., -2.), Vector3D(0., 0., 1.));
            Ray ray3(Point3D(0., 0., -2.), Vector3D(0., 0., -1.));
            assert_equal(*sphere.normalWithIntersection(ray1), IntersectParams{Vector3D(0., 0., -1.), Point3D(0., 0., -1.)});
            assert(!sphere.normalWithIntersection(ray3));
        }
    }, "Normal");
    std::cout << "Tests passed!\n\n";
}
