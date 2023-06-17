#include <Solutions/MatrixInv.hpp>
#include "../../../test_utils.hpp"

#include <iostream>

using namespace Math;
using namespace Math::Operators;

int main() {
    std::cout << "MATRIXINV\n";
    test([](){
    assert_equal_containers(*MatrixInv::getSolution(Matrix<4, 4>{
        { 1., 0., 0., 0. },
        { 0., 1., 0., 0. },
        { 0., 0., 1., 0. },
        { 0., 0., 0., 1. },
    }), std::vector<double>{1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1., 0., 0., 0., 0., 1.}, 16);
    }, "Simple");
    test([](){
    assert_equal_containers(*MatrixInv::getSolution(Matrix<4, 4>{
        { 1., 0., 0., 0. },
        { 0., 2., 0., 0. },
        { 0., 0., 4., 0. },
        { 0., 0., 0., 8. },
    }), std::vector<double>{1., 0., 0., 0., 0., 0.5, 0., 0., 0., 0., 0.25, 0., 0., 0., 0., 0.125}, 16);
    }, "Scaled");
    test([](){
    assert(MatrixInv::getSolution(Matrix<4, 4>{
        { 1., 0., 0., 0. },
        { 0., 1., 0., 0. },
        { 0., 0., 1., 0. },
        { 0., 0., 0., 0. },
    }) == std::nullopt);
    }, "Degenerate");
    test([](){
    assert_equal_containers(*MatrixInv::getSolution(Matrix<4, 4>{
        { 2., 2., -1., 1. },
        { 4., 3., -1., 2. },
        { 8., 5., -3., 4. },
        { 3., 3., -2., 2. },
    }), std::vector<double>{1., 1., -1., -4., -0.5, 0.5, 1.5, 1.5, 0.5, -0.5, -0.5, -0.5, -1., 0., 0., 2.}, 16);
    }, "Proskuryakov #1");
    std::cout << "Tests passed!\n\n";
}
