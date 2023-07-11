#include "BSPTree.hpp"

static bool placed_between(double lo, double v, double hi) {
    return lo <= v && v <= hi;
}

static void solve(double start, double add, double eq, double& v) {
    if (std::abs(add - 0) <= 1e-9) {
        return;
    }
    double ans = (eq - start) / add;
    if (ans > 0 && ans < v) {
        v = ans;
    }
}

std::optional<RayTracer::RenderingObjectParameters> Storage::BSPTree::lookupIntersection(const RayTracer::Ray& ray) const {
    Storage::Detail::ContainingCube ray_cube;
    std::optional<RayTracer::RenderingObjectParameters> collide_params = std::nullopt;
    const std::shared_ptr<Storage::Detail::BSPTreeNode>* node_ptr_ptr = &head_; 
    double t = 0;
    while (t >= 0) {
        Math::Point3D current_observation = ray.at(t);
        traverseUp(current_observation, &node_ptr_ptr, ray_cube);
        traverseDown(ray, current_observation, &node_ptr_ptr, ray_cube, collide_params, t > 0);
        t = transitionToNextNode(ray, ray_cube);
        if (collide_params.has_value() && t >= collide_params->params.k) {
            break;
        }
    }
    return collide_params;
}

void Storage::BSPTree::traverseDown(const RayTracer::Ray& ray, const Math::Point3D& current_obs,
const std::shared_ptr<Storage::Detail::BSPTreeNode>** current_node,
Detail::ContainingCube& cube, std::optional<RayTracer::RenderingObjectParameters>& colliding_params, bool skip) const {
    // Optimization: if we are traversing for second or more iteration, we simply skip first traverse
    if (!skip) {
        auto params = findClosestObject(ray, (**current_node)->objects_);
        if (params.has_value() && (!colliding_params.has_value() || params->params.k < colliding_params->params.k)) {
            colliding_params = params;
        }
    }

    // We will recursively limit the cube walls.
    int axis = static_cast<int>((**current_node)->division_axis_);
    if (current_obs[axis][0] < (**current_node)->division_value_ && (**current_node)->left_son_ != nullptr) {
        cube.limits[axis].first = (**current_node)->division_value_;
        *current_node = &(**current_node)->left_son_;
        traverseDown(ray, current_obs, current_node, cube, colliding_params, false);
    } else if ((**current_node)->right_son_ != nullptr) {
        cube.limits[axis].second = (**current_node)->division_value_;
        *current_node = &(**current_node)->right_son_;
        traverseDown(ray, current_obs, current_node, cube, colliding_params, false);
    }
}

void Storage::BSPTree::traverseUp(const Math::Point3D& current_obs, const std::shared_ptr<Detail::BSPTreeNode>** current_node,
Detail::ContainingCube& cube) const {
    if (placed_between(cube.x_limits.first, current_obs.x_, cube.x_limits.second) &&
        placed_between(cube.y_limits.first, current_obs.y_, cube.y_limits.second) &&
        placed_between(cube.z_limits.first, current_obs.z_, cube.z_limits.second)) {
        return;
    }
    int axis = static_cast<int>((**current_node)->division_axis_);
    if ((**current_node)->division_value_ < current_obs[axis][0]) {
        cube.limits[axis].first = (**current_node)->division_value_;
    } else {
        cube.limits[axis].second = (**current_node)->division_value_;
    }
    *current_node = &(**current_node)->parent_;
    traverseUp(current_obs, current_node, cube);
}

double Storage::BSPTree::transitionToNextNode(const RayTracer::Ray& ray, const Storage::Detail::ContainingCube& cube) const {
    double next = -1;
    solve(ray.source_.x_, ray.direction_.x_, cube.x_limits.first, next);
    solve(ray.source_.x_, ray.direction_.x_, cube.x_limits.second, next);
    solve(ray.source_.y_, ray.direction_.y_, cube.y_limits.first, next);
    solve(ray.source_.y_, ray.direction_.y_, cube.y_limits.second, next);
    solve(ray.source_.z_, ray.direction_.z_, cube.z_limits.first, next);
    solve(ray.source_.z_, ray.direction_.z_, cube.z_limits.second, next);
    return next + 1e-5;
}
