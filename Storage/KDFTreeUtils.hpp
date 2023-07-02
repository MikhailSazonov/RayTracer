#pragma once

#include "Scene.hpp"

#include <memory>

namespace Storage::Detail {
    enum class CuttingAxis {
        X = 0, Y = 1, Z = 2
    };

    enum class NodeBelonging {
        LEFT = -1, BOTH = 0, RIGHT = 1
    };

    struct KDFTreeNode {
        RayTracer::ObjectsPtrs objects_;
        std::unique_ptr<KDFTreeNode> left_son_;
        std::unique_ptr<KDFTreeNode> right_son_;

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
