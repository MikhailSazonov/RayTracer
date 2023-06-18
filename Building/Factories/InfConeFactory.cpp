#include "InfConeFactory.hpp"

InfConeFactory::InfConeFactory(){};

InfConeFactory::~InfConeFactory(){};

std::shared_ptr<Math::AFigure> InfConeFactory::createFigure(const libconfig::Setting &setting)
{
    int x, y, z;
    double t, s;

    const libconfig::Setting &color = setting.lookup("color");
    const libconfig::Setting &center = setting.lookup("center");

    setting.lookupValue("tan", t);
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

        return std::make_shared<Math::InfCone>(center_p, t, TransformerParser::getTransformer(setting), color_s, s);
    }

    return std::make_shared<Math::InfCone>(center_p, t);
}