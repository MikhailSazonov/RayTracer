#pragma once

#include "KDFTree.hpp"

Storage::KDFTree::KDFTree(const RayTracer::Scene& scene)
    :
        sources_(scene.lights_)
{
    InitHead(scene);
    CreateChildren(head);
}

void Storage::KDFTree::CreateChildren(std::unique_ptr<Storage::Detail::KDFTreeNode>& node,
size_t dividing_axis_index, size_t recursion_depth) {
    using namespace Storage::Detail;

    if (recursion_depth == MAX_TREE_DEPTH || node->objects_.size() <= MIN_OBJECTS_IN_NODE) {
        return;
    }

    node->division_axis_ = order_of_cutting[dividing_axis_index];
    node->division_value_ = PickDividingValue(node->objects_, node->division_axis_);
    ObjectsPtrs left_set;
    ObjectsPtrs right_set;

    for (auto& obj_ptr : node->objects_) {
        NodeBelonging belonging = DetermineBelonging(*obj_ptr, node->division_axis_, node->division_value_);
        switch (belonging) {
            case NodeBelonging::LEFT:
                left_set.insert(obj_ptr);
                break;
            case NodeBelonging::RIGHT;
                right_Set.insert(obj_ptr);
                break;
        }
    }

    if (left_set.empty() || right_set.empty()) {
        // One of the children is empty: we pick next axis for the same node
        CreateChildren(node, (dividing_axis_index + 1) % order_of_cutting.size(), recursion_depth + 1);
        return;
    }

    for (auto& obj_ptr : left_set) {
        node->objects_.erase(obj_ptr);
    }
    for (auto& obj_ptr : right_set) {
        node->objects_.erase(obj_ptr);
    }

    if (!left_set.empty()) {
        node->left_son_.reset(new KDFTreeNode());
        node->left_son->objects_ = left_set;
        CreateChildren(node->left_son, (dividing_axis_index + 1) % order_of_cutting.size(), recursion_depth + 1);
    }

    if (!right_set.empty()) {
        node->right_son_.reset(new KDFTreeNode());
        node->right_son_->objects_ = right_set;
        CreateChildren(node->right_son_, (dividing_axis_index + 1) % order_of_cutting.size(), recursion_depth + 1);
    }

}
