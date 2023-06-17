#include <Basics/Vector3D.hpp>
#include "../../test_utils.hpp"

#include <iostream>

using namespace Math;

int main() {
    std::cout << "VECTOR\n";
    test([](){
        // BASICS
        Vector3D vec_default;
        Vector3D vec_custom(1., 2., 3.);
        Vector3D shiny_vector(vec_default);
        Vector3D ultimate_answer(Vector3D(42., 42., 42.));
        vec_custom = vec_default;
        vec_custom = Vector3D(4., 5., 6.);
    }, "Basic");
    test([](){
        // SUMM + SUBTRACT
        Vector3D vec1(1., 2., 3.);
        Vector3D vec2(2., 4., 6.);
        Vector3D result = vec2;
        assert_equal(vec1 + vec1, result);
        vec1 += vec2 + vec1;
        assert_equal(vec1, result + result);

        vec1 -= vec2 + vec2;
        assert_zero(vec1);

        vec1 = vec2 - vec1;
        assert_equal(vec1, vec2);
    }, "Summ + Subtract");
    test([](){
        // MULTI + DIVIDE
        Vector3D vec1(1., 2., 3.);
        Vector3D vec2(5., 5., 5.);
        vec1 *= vec2;
        assert_equal(vec1, Vector3D(1., 2., 3.) * 5.);
        vec1 = vec1 * vec2;
        assert_equal(vec1, Vector3D(1., 2., 3.) * 25.);

        Vector3D vec3(1., 4., 9.);
        Vector3D vec4(1., 2., 3.);
        vec3 /= vec4;
        assert_equal(vec3, Vector3D(2., 4., 6.) / 2.);
        vec3 = vec3 / vec4;
        assert_equal(vec3, Vector3D(1., 1., 1.));
    }, "Multi + Divide");
    test([](){
        // DOT
        Vector3D vec1(1., 2., 3.);
        Vector3D vec2(1., 2., 3.);
        double vec3 = vec1.dot(vec2);
        assert_equal(vec3, 14.);
    }, "Dot");
    std::cout << "Tests passed!\n\n";
}