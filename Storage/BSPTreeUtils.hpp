#pragma once

#include "Scene.hpp"

#include <memory>
#include <limits>

namespace Storage::Detail {
    enum class CuttingAxis {
        X = 0, Y = 1, Z = 2
    };

    struct ContainingCube {
        std::pair<double, double> limits[3]{{-std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity()},
                                            {-std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity()},
                                            {-std::numeric_limits<double>::infinity(),
            std::numeric_limits<double>::infinity()}};

        std::pair<double, double>& x_limits{limits[0]};
        std::pair<double, double>& y_limits{limits[1]};
        std::pair<double, double>& z_limits{limits[2]};
    };

    enum class NodeBelonging {
        LEFT = -1, BOTH = 0, RIGHT = 1
    };

    struct BSPTreeNode {
        std::shared_ptr<BSPTreeNode> parent_;
        RayTracer::ObjectsPtrs objects_;
        std::shared_ptr<BSPTreeNode> left_son_;
        std::shared_ptr<BSPTreeNode> right_son_;

        // The axis on which left and right son are divided.
        CuttingAxis division_axis_;
        // The value, on which division is made.
        double division_value_;
    };

    // Seems to have no difference with permutations.
    inline static const std::vector<CuttingAxis> order_of_cutting{CuttingAxis::X, CuttingAxis::Y, CuttingAxis::Z};

    inline static const size_t MAX_TREE_DEPTH = 15;
    inline static const size_t MIN_OBJECTS_IN_NODE = 5;
}
