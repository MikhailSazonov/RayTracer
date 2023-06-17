#include "PointLight.hpp"

#include <iostream>

namespace RayTracer
{

    PointLight::PointLight(const Math::Point3D &position, const Math::Vector3D &color,
                           double diffuse_coef, double specular_coef)
        : ASource(color), position_(position),
          diffuse_coef_(diffuse_coef), specular_coef_(specular_coef)
    {}

    bool PointLight::isShadowed(const Ray& ray,
    const std::vector<std::shared_ptr<Math::AFigure>>& objects) {
        if (Settings::isFast()) {
            return false;
        }
        auto intersect_params = findClosestObject(ray, objects);
        if (!intersect_params.has_value()) {
            return false;
        }
        double distance_from_object = Math::Vector3D(intersect_params->params.intersection - ray.source_).length();
        double distance_from_light = ray.direction_.length();
        return distance_from_object < distance_from_light;
    }

    std::optional<Math::Vector3D> PointLight::getColor(const Ray &ray, const Math::Vector3D &normal, double surface_receptivity,
                                                       const std::vector<std::shared_ptr<Math::AFigure>> &figures)
    {
        Math::Vector3D light_direction = position_ - ray.source_;

        double cosin_spec = Math::cos(ray.direction_, light_direction);
        double cosin_diffuse = Math::cos(normal, light_direction);

        // 1. The direction of ray is bad
        // 2. Shadows
        if ((cosin_spec <= 0 && cosin_diffuse <= 0) || isShadowed(Ray(ray.source_, light_direction), figures)) {
            return std::nullopt;
        }

        Math::Vector3D result;
        if (cosin_diffuse > 0)
        {
            result += color_ * cosin_diffuse * diffuse_coef_;
        }
        if (cosin_spec > 0)
        {
            result += color_ * pow(cosin_spec, surface_receptivity) * specular_coef_;
        }

        // Attenuation based on distance (decay of light)
        // double attenuation = 1.0 / (distance * distance);
        // result *= attenuation;

        return result;
    }

}
