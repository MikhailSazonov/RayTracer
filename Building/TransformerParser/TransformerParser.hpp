#pragma once

#include <libconfig.h++>

#include <Transformers/RotationTransformers/RotationTransformerX.hpp>
#include <Transformers/RotationTransformers/RotationTransformerY.hpp>
#include <Transformers/RotationTransformers/RotationTransformerZ.hpp>

#include <Transformers/ShearTransformers/ShearTransformerX.hpp>
#include <Transformers/ShearTransformers/ShearTransformerY.hpp>
#include <Transformers/ShearTransformers/ShearTransformerZ.hpp>

#include <Transformers/ATransformer.hpp>
#include <Transformers/BaseTransformer.hpp>
#include <Transformers/CustomTransformer.hpp>
#include <Transformers/ScalingTransformer.hpp>
#include <Transformers/TranslationTransformer.hpp>

#include <memory>

namespace TransformerParser
{
    //! @brief The function to get the transformer from a libconfig setting
    Math::Operators::BaseTransformer getTransformer(const libconfig::Setting &setting);
}

