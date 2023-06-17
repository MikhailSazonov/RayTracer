#include "PlaneFactory.hpp"

PlaneFactory::PlaneFactory(){};

PlaneFactory::~PlaneFactory(){};

std::shared_ptr<Math::AFigure> PlaneFactory::createFigure(const libconfig::Setting &setting)
{
    int x, y, z;

    // Math::Point3D point = Math::Point3D(x, y, z);
    const libconfig::Setting &point = setting.lookup("point");
    const libconfig::Setting &normal = setting.lookup("normal");
    const libconfig::Setting &color = setting.lookup("color");

    if (!point.isAggregate() || !normal.isAggregate())
        throw std::runtime_error("Plane was bad declared. Specify normal{} and point{}");

    point.lookupValue("x", x);
    point.lookupValue("y", y);
    point.lookupValue("z", z);
    Math::Point3D p = Math::Point3D(x, y, z);

    normal.lookupValue("x", x);
    normal.lookupValue("y", y);
    normal.lookupValue("z", z);
    Math::Vector3D n = Math::Vector3D(x, y, z);

    if (color.isAggregate())
    {
        int red, g, b;
        color.lookupValue("r", red);
        color.lookupValue("g", g);
        color.lookupValue("b", b);
        size_t color = ((size_t)red << 16) | ((size_t)g << 8) | (size_t)b;

        return std::make_shared<Math::Plane>(p, n, TransformerParser::getTransformer(setting), color);
    }

    return std::make_shared<Math::Plane>(p, n);
}