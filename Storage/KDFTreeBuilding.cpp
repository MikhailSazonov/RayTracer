#include "KDFTree.hpp"

Storage::KDFTree::KDFTree(const RayTracer::Scene& scene)
    :
        sources_(scene.lights_)
{
    gen.seed(std::time(nullptr));
    InitHead(scene);
    CreateChildren(head_);
}

void Storage::KDFTree::CreateChildren(std::shared_ptr<Storage::Detail::KDFTreeNode>& node,
size_t dividing_axis_index, size_t recursion_depth) {
    using namespace Storage::Detail;

    if (recursion_depth == MAX_TREE_DEPTH || node->objects_.size() <= MIN_OBJECTS_IN_NODE) {
        return;
    }

    node->division_axis_ = order_of_cutting[dividing_axis_index];
    node->division_value_ = PickDividingValue(node->objects_, node->division_axis_);
    RayTracer::ObjectsPtrs left_set;
    RayTracer::ObjectsPtrs right_set;

    for (auto* obj_ptr : node->objects_) {
        NodeBelonging belonging = DetermineBelonging(**obj_ptr, node->division_axis_, node->division_value_);
        switch (belonging) {
            case NodeBelonging::LEFT:
                left_set.insert(obj_ptr);
                break;
            case NodeBelonging::RIGHT:
                right_set.insert(obj_ptr);
                break;
            default:
                break;
        }
    }

    for (auto* left_ptr : left_set) {
        node->objects_.erase(left_ptr);
    }

    for (auto* right_ptr : right_set) {
        node->objects_.erase(right_ptr);
    }

    if (!left_set.empty()) {
        node->left_son_.reset(new KDFTreeNode());
        node->left_son_->parent_ = node;
        node->left_son_->objects_ = left_set;
        CreateChildren(node->left_son_, (dividing_axis_index + 1) % order_of_cutting.size(), recursion_depth + 1);
    }

    if (!right_set.empty()) {
        node->right_son_.reset(new KDFTreeNode());
        node->right_son_->parent_ = node;
        node->right_son_->objects_ = right_set;
        CreateChildren(node->right_son_, (dividing_axis_index + 1) % order_of_cutting.size(), recursion_depth + 1);
    }
}

void Storage::KDFTree::InitHead(const RayTracer::Scene& scene) {
    head_.reset(new Storage::Detail::KDFTreeNode());
    for (auto& obj_unique_ptr : scene.objects_) {
        head_->objects_.insert(&obj_unique_ptr);
    }
}

double Storage::KDFTree::PickDividingValue(const RayTracer::ObjectsPtrs& obj_refs, Detail::CuttingAxis dividing_axis) {
    size_t idx = gen() % obj_refs.size();
    auto iter = obj_refs.begin();
    for (size_t i = 0; i < idx; ++i) {
        ++iter;
    }
    switch (dividing_axis) {
        case Storage::Detail::CuttingAxis::X:
            return (**iter)->getBox().basement_point_.x_ - 1e-5;
        case Storage::Detail::CuttingAxis::Y:
            return (**iter)->getBox().basement_point_.y_ - 1e-5;
        case Storage::Detail::CuttingAxis::Z:
            return (**iter)->getBox().basement_point_.z_ - 1e-5;
    }
    return 0;
}

Storage::Detail::NodeBelonging Storage::KDFTree::DetermineBelonging(const Math::AFigure& figure, Detail::CuttingAxis dividing_axis, double dividing_value) {
    const auto& box = figure.getBox();
    if ((dividing_axis == Storage::Detail::CuttingAxis::X && box.x_vect_.limit_ == Math::Detail::Length::UNLIMITED) || 
            (dividing_axis == Storage::Detail::CuttingAxis::Y && box.y_vect_.limit_ == Math::Detail::Length::UNLIMITED) || 
                (dividing_axis == Storage::Detail::CuttingAxis::Z && box.z_vect_.limit_ == Math::Detail::Length::UNLIMITED))
    {
        return Storage::Detail::NodeBelonging::BOTH;
    }
    Math::Point3D p[8];
    p[0] = box.basement_point_;
    p[1] = box.basement_point_ + box.x_vect_.direction_;
    p[2] = box.basement_point_ + box.y_vect_.direction_;
    p[3] = box.basement_point_ + box.x_vect_.direction_ + box.y_vect_.direction_;
    p[4] = box.basement_point_ + box.z_vect_.direction_;
    p[5] = box.basement_point_ + box.z_vect_.direction_ + box.x_vect_.direction_;
    p[6] = box.basement_point_ + box.z_vect_.direction_ + box.y_vect_.direction_;
    p[7] = box.basement_point_ + box.z_vect_.direction_ + box.y_vect_.direction_ + box.x_vect_.direction_;
    return CompareThePoints(p, static_cast<int>(dividing_axis), dividing_value);
}

Storage::Detail::NodeBelonging Storage::KDFTree::CompareThePoints(Math::Point3D* points, int index, double dividing_value) {
    bool left = true;
    bool right = true;
    for (int i = 0; i < 8; ++i) {
        if (points[i][index][0] < dividing_value) {
            right = false;
        }
        if (points[i][index][0] >= dividing_value) {
            left = false;
        }
    }
    if (left ^ right) {
        if (left) {
            return Storage::Detail::NodeBelonging::LEFT;
        }
        if (right) {
            return Storage::Detail::NodeBelonging::RIGHT;
        }
    }
    return Storage::Detail::NodeBelonging::BOTH;
}
