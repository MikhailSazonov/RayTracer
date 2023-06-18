#include "InfCylinderFactory.hpp"

InfCylinderFactory::InfCylinderFactory(){};

InfCylinderFactory::~InfCylinderFactory(){};

std::shared_ptr<Math::AFigure> InfCylinderFactory::createFigure(const libconfig::Setting &setting)
{
    int x, y, z;
    double r, s;

    const libconfig::Setting &color = setting.lookup("color");
    const libconfig::Setting &center = setting.lookup("center");

    setting.lookupValue("radius", r);
    setting.lookupValue("specular", s);

    center.lookupValue("x", x);
    center.lookupValue("y", y);
    center.lookupValue("z", z);
    Math::Point3D center_p = Math::Point3D(x, y, z);

    if (color.isAggregate())
    {
        int red, g, b;
        color.lookupValue("r", red);
        color.lookupValue("g", g);
        color.lookupValue("b", b);
        size_t color_s = ((size_t)red << 16) | ((size_t)g << 8) | (size_t)b;

        return std::make_shared<Math::InfCylinder>(center_p, r, TransformerParser::getTransformer(setting), color_s, s);
    }

    return std::make_shared<Math::InfCylinder>(center_p, r);
}
