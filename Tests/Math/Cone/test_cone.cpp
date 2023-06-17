#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include <Figures/Cone.hpp>
#include "../../test_utils.hpp"

#include <iostream>

using namespace Math;
using namespace RayTracer;

int main() {
    std::cout << "Cone\n";
    test([](){
        Cone cone(Point3D(0., 0., 0.), 3., 3.);
        {
            Ray ray1(Point3D(-4., 1., 0.), Vector3D(1., 0., 0.));
            Ray ray2(Point3D(4., 1., 0.), Vector3D(-1., 0., 0.));
            Ray ray3(Point3D(4., 1., 0.), Vector3D(1., 0., 0.));
            auto params1 = cone.normalWithIntersection(ray1);
            auto params2 = cone.normalWithIntersection(ray2);
            auto params3 = cone.normalWithIntersection(ray3);
            assert(params1);
            assert(params2);
            assert(!params3);
            assert_equal(params1->intersection, Point3D(-2., 1., 0.));
            assert_equal(params1->normal, Vector3D(-2., 2., 0.));
            assert_equal(params2->intersection, Point3D(2., 1., 0.));
            assert_equal(params2->normal, Vector3D(2., 2., 0.));
        }
    }, "Side");
    test([](){
        Cone cone(Point3D(0., 0., 0.), 2., 2.);
        {
            Ray ray1(Point3D(0., -1., 0.), Vector3D(-1., 1., 0.));
            Ray ray2(Point3D(0., -1., 0.), Vector3D(1., 1., 0.));
            Ray ray3(Point3D(0., -1., 0.), Vector3D(-4., 1., 0.));
            auto params1 = cone.normalWithIntersection(ray1);
            auto params2 = cone.normalWithIntersection(ray2);
            auto params3 = cone.normalWithIntersection(ray3);
            assert(params1);
            assert(params2);
            assert(!params3);
            assert_equal(params1->intersection, Point3D(-1., 0., 0.));
            assert_equal(params1->normal, Vector3D(0., -1., 0.));
            assert_equal(params2->intersection, Point3D(1., 0., 0.));
            assert_equal(params2->normal, Vector3D(0., -1., 0.));
        }
    }, "Bottom");
    test([](){
        Cone cone(Point3D(0., 0., 5.), 3., 3.);
        {
            Ray ray1(Point3D(-4., 1., 5.), Vector3D(1., 0., 0.));
            Ray ray2(Point3D(4., 1., 5.), Vector3D(-1., 0., 0.));
            Ray ray3(Point3D(4., 1., 5.), Vector3D(1., 0., 0.));
            auto params1 = cone.normalWithIntersection(ray1);
            auto params2 = cone.normalWithIntersection(ray2);
            auto params3 = cone.normalWithIntersection(ray3);
            assert(params1);
            assert(params2);
            assert(!params3);
            assert_equal(params1->intersection, Point3D(-2., 1., 5.));
            assert_equal(params1->normal, Vector3D(-2., 2., 0.));
            assert_equal(params2->intersection, Point3D(2., 1., 5.));
            assert_equal(params2->normal, Vector3D(2., 2., 0.));
        }
    }, "Side + shift");
        test([](){
        Cone cone(Point3D(3., 0., 5.), 2., 2.);
        {
            Ray ray1(Point3D(3., -1., 5.), Vector3D(-1., 1., 0.));
            Ray ray2(Point3D(3., -1., 5.), Vector3D(1., 1., 0.));
            Ray ray3(Point3D(3., -1., 5.), Vector3D(-4., 1., 0.));
            auto params1 = cone.normalWithIntersection(ray1);
            auto params2 = cone.normalWithIntersection(ray2);
            auto params3 = cone.normalWithIntersection(ray3);
            assert(params1);
            assert(params2);
            assert(!params3);
            assert_equal(params1->intersection, Point3D(2., 0., 5.));
            assert_equal(params1->normal, Vector3D(0., -1., 0.));
            assert_equal(params2->intersection, Point3D(4., 0., 5.));
            assert_equal(params2->normal, Vector3D(0., -1., 0.));
        }
    }, "Bottom + shift");
    std::cout << "Tests passed!\n\n";
}
