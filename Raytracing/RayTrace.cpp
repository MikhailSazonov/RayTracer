#include "RayTrace.hpp"

#include <limits>

#include <iostream>

static void Transfuse(double& source, double& first, double& second, double limit = 255.) {
    if (source > limit) {
        float overhead = source - limit;
        source = limit;
        first += overhead / 2;
        second += overhead / 2;
    }
}

void RayTracer::RedistributeTheLights(Math::Vector3D& lights) {
    Transfuse(lights.x_, lights.y_, lights.z_);
    Transfuse(lights.y_, lights.x_, lights.z_);
    Transfuse(lights.z_, lights.x_, lights.y_);
    lights.x_ = std::min(255., lights.x_);
    lights.y_ = std::min(255., lights.y_);
    lights.z_ = std::min(255., lights.z_);
}

bool RayTracer::isOverlap(const Ray& ray,
const std::vector<std::shared_ptr<Math::AFigure>>& objects) {
    // Scanning for the object that we could collide with.
    for (auto& object : objects) {
        // if the ray was reflected, and we meet another object, put shadow
        // or if the ray was reflected and there are no light sources on the way
        auto intersect_params = object->normalWithIntersection(ray);
        if (intersect_params != std::nullopt) {
            double distance = (intersect_params->intersection - ray.source_).length();
            if (distance > 1e-9) {
                return true;
            }
        }
    }
    return false;
}

std::optional<RayTracer::RenderingObjectParameters> RayTracer::findClosestObject(const Ray& ray,
const std::vector<std::shared_ptr<Math::AFigure>>& objects) {
    double min_distance = std::numeric_limits<double>::infinity();
    std::optional<RayTracer::RenderingObjectParameters> closest_object_params = std::nullopt;
    // Scanning for the object that we could collide with.
    // The closest object wins
    for (auto& object : objects) {
        // if the ray was reflected, and we meet another object, put shadow
        // or if the ray was reflected and there are no light sources on the way
        auto intersect_params = object->normalWithIntersection(ray);
        if (intersect_params != std::nullopt) {
            double distance = (intersect_params->intersection - ray.source_).length();
            if (distance < min_distance && distance > 1e-9) {
                min_distance = distance;
                closest_object_params = {*intersect_params,
                                        object->getColorReaction(),
                                        object->getSpecularCoef()};
            }
        }
    }
    return closest_object_params;
}

Math::Vector3D RayTracer::RayTrace(const RayTracer::Objects& objects, const RayTracer::Sources &lights, RayTracer::Ray& ray) {
    // flag for the reflection:
    auto obj_params = findClosestObject(ray, objects);
    if (!obj_params.has_value()) {
        // sky is over
        // TODO: put in enum
        return Math::Vector3D((double)0x87, (double)0xCE, (double)0xEB);
    }
    // Here the ray was reflected
    ray.ReflectInPlace(obj_params->params.intersection, obj_params->params.normal);
    Math::Vector3D color;
    for (auto& lights : lights) {
        std::optional<Math::Vector3D> next_color;
        if ((next_color = lights->getColor(ray, obj_params->params.normal,
        obj_params->specular_coef, objects)) != std::nullopt) {
            color += *next_color;
        }
    }
    color *= obj_params->color_reaction;
    // if we have > 255. for one of the colors,
    // we distribute the overhead between two other colors,
    // this will make it more bright without changing the color (from red to red-plus-green for example)
    RedistributeTheLights(color);
    return color;
}

size_t RayTracer::convertToRGB(const Math::Vector3D& color_vector) {
    return (static_cast<int>(color_vector.x_) << 16) + (static_cast<int>(color_vector.y_) << 8) + static_cast<int>(color_vector.z_);
}
