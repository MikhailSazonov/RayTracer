#pragma once

#include "IFigure.hpp"
#include "AlgorithmsTools/Box.hpp"
#include <Basics/Matrix.hpp>
#include <Transformers/ATransformer.hpp>
#include <Transformers/BaseTransformer.hpp>

#include <memory>

namespace Math
{
    class AFigure : public IFigure
    {
    protected:
        AFigure(size_t color, double specular_coef,
                const Operators::ATransformer &transformer);

    public:
        inline const Vector3D &getColorReaction() const override
        {
            return color_coef_;
        }

        inline double getSpecularCoef() const override
        {
            return specular_coef_;
        }

        std::optional<IntersectParams> normalWithIntersection(const RayTracer::Ray &);

        inline const Box& getBox() {
            return box_;
        }

    protected:
        virtual std::optional<IntersectParams> innerNormalWithIntersection(const RayTracer::Ray &) = 0;

        virtual void MakeBox() = 0;

    protected:
        Vector3D color_coef_;
        double specular_coef_;
        std::unique_ptr<Operators::ATransformer> transformer_;
        Box box_;
    };
}

