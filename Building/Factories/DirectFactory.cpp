#include "DirectFactory.hpp"

DirectFactory::DirectFactory(){};

DirectFactory::~DirectFactory(){};

std::unique_ptr<RayTracer::ISource> DirectFactory::createSource(const libconfig::Setting &setting)
{
    int x, y, z;
    double diffuse, specular;

    const libconfig::Setting &color = setting.lookup("color");
    const libconfig::Setting &direction = setting.lookup("direction");

    if (!direction.isAggregate())
        throw std::runtime_error("Plane was bad declared. Specify direction{}");

    direction.lookupValue("x", x);
    direction.lookupValue("y", y);
    direction.lookupValue("z", z);
    Math::Vector3D v = Math::Vector3D(x, y, z);

    setting.lookupValue("diffuse", diffuse);
    setting.lookupValue("specular", specular);

    if (color.isAggregate())
    {
        int red, g, b;
        color.lookupValue("r", red);
        color.lookupValue("g", g);
        color.lookupValue("b", b);
        Math::Vector3D colorVec = Math::Vector3D(red, g, b);

        return std::make_unique<RayTracer::DirectIllumination>(v, colorVec, diffuse, specular);
    }

    return std::make_unique<RayTracer::DirectIllumination>(v);
}