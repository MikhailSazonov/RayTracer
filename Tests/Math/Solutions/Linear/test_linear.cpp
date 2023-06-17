#include <Solutions/Linear4x.hpp>
#include "../../../test_utils.hpp"

#include <iostream>

using namespace Math;
using namespace Math::Operators;

int main() {
    std::cout << "LINEAR4X\n";
    test([](){
        assert_equal_containers(*Linear4x::getSolution(Matrix<4, 4>{
            { 1., 0., 0., 0. },
            { 0., 1., 0., 0. },
            { 0., 0., 1., 0. },
            { 0., 0., 0., 1. },
        }, Matrix<4, 1>{
            1., 2., 3., 4.
        }), std::vector<double>{1., 2., 3., 4.}, 4);
    }, "Simple");
    test([](){
    assert_equal_containers(*Linear4x::getSolution(Matrix<4, 4>{
        { 1., 0., 0., 0. },
        { 0., 2., 0., 0. },
        { 0., 0., 3., 0. },
        { 0., 0., 0., 4. },
    }, Matrix<4, 1>{
        1., 2., 3., 4.
    }), std::vector<double>{1., 1., 1., 1.}, 4);
    }, "Scaling");
    test([](){
    assert(Linear4x::getSolution(Matrix<4, 4>{
        { 1., 0., 0., 0. },
        { 0., 2., 0., 0. },
        { 0., 0., 3., 0. },
        { 0., 0., 0., 0. },
    }, Matrix<4, 1>{
        1., 2., 3., 4.
    }) == std::nullopt);
    }, "No solution #1");
    test([](){
    assert(Linear4x::getSolution(Matrix<4, 4>{
        { 1., 1., 1., 1. },
        { 2., 2., 2., 2. },
        { 0., 0., 3., 0. },
        { 0., 0., 0., 4. },
    }, Matrix<4, 1>{
        1., 2., 3., 4.
    }) == std::nullopt);
    }, "No solution #2");
    test([](){
    assert_equal_containers(*Linear4x::getSolution(Matrix<4, 4>{
        { 2., 2., -1., 1. },
        { 4., 3., -1., 2. },
        { 8., 5., -3., 4. },
        { 3., 3., -2., 2. },
    }, Matrix<4, 1>{
        4., 6., 12., 6.
    }), std::vector<double>{1, 1, -1, -1}, 4);
    }, "Proskuryakov #1");
    test([](){
    assert_equal_containers(*Linear4x::getSolution(Matrix<4, 4>{
        { 2., 3., 11., 5. },
        { 1., 1., 5., 2. },
        { 2., 1., 3., 2. },
        { 1., 1., 3., 4. },
    }, Matrix<4, 1>{
        2., 1., -3., -3.
    }), std::vector<double>{-2, 0, 1, -1}, 4);
    }, "Proskuryakov #2");
        test([](){
    assert_equal_containers(*Linear4x::getSolution(Matrix<4, 4>{
        { 3., 4., 1., 2. },
        { 3., 5., 3., 5. },
        { 6., 8., 1., 5. },
        { 3., 5., 3., 7. },
    }, Matrix<4, 1>{
        -3., -6., -8., -8.
    }), std::vector<double>{2, -2, 1, -1}, 4);
    }, "Proskuryakov #3");
    std::cout << "Tests passed!\n\n";
}
