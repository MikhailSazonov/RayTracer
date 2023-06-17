#include "AmbientLight.hpp"

AmbiantLightFactory::AmbiantLightFactory()
{
}

AmbiantLightFactory::~AmbiantLightFactory()
{
}

std::unique_ptr<RayTracer::ISource> AmbiantLightFactory::createSource(const libconfig::Setting &setting)
{
    const libconfig::Setting &color = setting.lookup("color");
    if (color.isAggregate()) {
        int r, g, b;
        color.lookupValue("r", r);
        color.lookupValue("g", g);
        color.lookupValue("b", b);
        Math::Vector3D colorVec = Math::Vector3D(r, g, b);

        return std::make_unique<RayTracer::AmbientIllumination>(colorVec);
    }

    return std::make_unique<RayTracer::AmbientIllumination>();
}
