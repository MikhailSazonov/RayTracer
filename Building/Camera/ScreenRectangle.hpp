#pragma once

#include <Basics/Vector3D.hpp>
#include <Basics/Point3D.hpp>

namespace RayTracer
{
    class ScreenRectangle
    {
        friend class Camera;

    public:
        /**
         * @brief ScreenRectangle constructor.
         *
         * rectangle starts from bottom left corner
         *
         * @param start Starting point of the rectangle.
         * @param right_vector right side of the rectangle in 3D space (->).
         * @param up_vector  Upside side of the rectangle in 3D space (|^).
         */
        ScreenRectangle(const Math::Point3D &, const Math::Vector3D &, const Math::Vector3D &);

        /**
         * @brief Converts 2D coordinates to 3D coordinates.
         *
         * @param u 2D coordinate on the x axis.
         *
         * @param v 2D coordinate on the y axis.
         * @return Math::Point3D 3D coordinates.
         */
        Math::Point3D pointAt(double u, double v) const;

    public:
        Math::Point3D left_bottom_;
        Math::Vector3D left_side_;
        Math::Vector3D bottom_side_;
    };

}
