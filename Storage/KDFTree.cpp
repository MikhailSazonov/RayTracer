#pragma once

#include "KDFTree.hpp"

Storage::KDFTree::KDFTree(const RayTracer::Scene& scene)
    :
        sources_(scene.lights_)
{
    gen.seed(std::time(nullptr));
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

void Storage::KDFTree::InitHead(const RayTracer::Scene& scene) {
    head_.reset(new KDFTreeNode());
    for (auto& obj_unique_ptr : scene.objects_) {
        head_->objects_.insert(&obj_unique_ptr);
    }
}

double Storage::KDFTree::PickDividingValue(const RayTracer::ObjectsPtrs& obj_refs, Detail::CuttingAxis dividing_axis) {
    size_t idx = gen() % obj_refs.size();
    switch dividing_axis {
        case X:
            return obj_refs[idx].getBox().basement_point_.x_ - 1e5;
        case Y:
            return obj_refs[idx].getBox().basement_point_.y_ - 1e5;
        case Z:
            return obj_refs[idx].getBox().basement_point_.z_ - 1e5;
    }
    return 0;
}

Detail::NodeBelonging Storage::KDFTree::DetermineBelonging(const Math::AFigure& figure, Detail::CuttingAxis dividing_axis, double dividing_value) {
    auto& box = figure.getBox();
    if (dividing_axis == Detail::CuttingAxis::X && box.x_vect_.limit_ == Math::Detail::Length::UNLIMITED || 
            dividing_axis == Detail::CuttingAxis::Y && box.y_vect_.limit_ == Math::Detail::Length::UNLIMITED || 
                dividing_axis == Detail::CuttingAxis::Z && box.z_vect_.limit_ == Math::Detail::Length::UNLIMITED)
    {
        return Detail::NodeBelonging::BOTH;
    }
    Math::Point3D p[8];
    p[0] = box.basement_point_;
    p[1] = box.basement_point_ + box.x_vect_;
    p[2] = box.basement_point_ + box.y_vect_;
    p[3] = box.basement_point_ + box.x_vect_ + box.y_vect_;
    p[4] = box.basement_point_ + box.z_vect_;
    p[5] = box.basement_point_ + box.z_vect_ + box.x_vect_;
    p[6] = box.basement_point_ + box.z_vect_ + box.y_vect_;
    p[7] = box.basement_point_ + box.z_vect_ + box.y_vect + box.x_vect_;
    return CompareThePoints(p, static_cast<int>(dividing_axis), dividing_value);
}

Detail::NodeBelonging Storage::KDFTree::CompareThePoints(Math::Point3D* points, int index, double dividing_value) {
    bool left = true;
    bool right = true;
    for (int i = 0; i < 8; ++i) {
        if (points[i][index] < dividing_value) {
            right = false;
        }
        if (points[i][index] >= dividing_value) {
            left = false;
        }
    }
    if (left ^ right) {
        if (left) {
            return Detail::NodeBelonging::LEFT
        }
        if (right) {
            return Detail::NodeBelonging::RIGHT;
        }
    }
    return Detail::NodeBelonging::BOTH;
}
