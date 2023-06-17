#include <Basics/Point3D.hpp>
#include <Basics/Vector3D.hpp>
#include "../../test_utils.hpp"

#include <iostream>

using namespace Math;

int main() {
    std::cout << "POINT\n";
    test([](){
        // BASICS
        Point3D p_default;
        Point3D p_custom(1., 2., 3.);
        Point3D p_cp(p_default);
        Point3D p_mv(Point3D(0., 0., 0.));
        p_custom = p_default;
        p_custom = Point3D(4., 5., 6.);
    }, "Basic");
    test([](){
        // SUMM
        Vector3D vec1(1., 2., 3.);
        Point3D p1(2., 4., 6.);
        assert_equal(p1 + vec1, Point3D(3., 6., 9.));

        p1 += vec1;
        assert_equal(p1, Point3D(3., 6., 9.));
    }, "Summ");
    test([](){
        // SUB
        Vector3D vec1(1., 2., 3.);
        Point3D p1(2., 4., 6.);
        assert_equal(p1 - vec1, Point3D(1., 2., 3.));

        p1 -= vec1;
        p1 -= vec1;
        assert_zero(p1);

        Point3D p2(2., 4., 6.);
        Point3D p3(1., 3., 5.);
        assert_equal(p2 - p3, Vector3D(1., 1., 1.));
    }, "Subtract");
    std::cout << "Tests passed!\n\n";
}
