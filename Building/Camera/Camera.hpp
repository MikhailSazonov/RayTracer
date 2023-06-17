#pragma once

#include "ScreenRectangle.hpp"

#include <Basics/Point3D.hpp>
#include <Basics/Matrix.hpp>
#include <Illumination/Ray.hpp>

#include <Transformers/ATransformer.hpp>
#include <Transformers/BaseTransformer.hpp>

namespace RayTracer
{

    class Camera
    {
    public:
        /**
         * @brief Camera constructor.
         * Creates a camera from which rays will be casted.
         * @param fieldOfView Field of view of the camera. default: 90.
         * @param resolution Resolution of the camera. default: {1920, 1080}.
         * @param transformer Transformer of the camera. default: BaseTransformer.
         */
        Camera(double fieldOfView = 90.,
               const std::pair<size_t, size_t> resolution = {1920, 1080},
               const Math::Operators::ATransformer &transformer = Math::Operators::BaseTransformer());

        //! @brief Casts a ray from the camera to the screen.
        Ray ray(double u, double v) const;

        inline const Math::Point3D &getOrigin()
        {
            return origin_;
        }

        //! @brief Returns the screen width.
        inline size_t getWidth() const
        {
            return resolution_.first;
        }

        //! @brief Returns the screen height.
        inline size_t getHeight() const
        {
            return resolution_.second;
        }

    private:
        Math::Point3D origin_;                 //!< Origin of the camera.
        ScreenRectangle screen_;               //!< Screen of the camera.
        std::pair<size_t, size_t> resolution_; //!< Resolution of the camera.
    };

}
