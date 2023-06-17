#include "SphereFactory.hpp"

SphereFactory::SphereFactory(){};

SphereFactory::~SphereFactory(){};

std::shared_ptr<Math::AFigure> SphereFactory::createFigure(const libconfig::Setting &setting)
{
    double x, y, z;
    double r;
    setting.lookupValue("x", x);
    setting.lookupValue("y", y);
    setting.lookupValue("z", z);
    setting.lookupValue("r", r);

    Math::Point3D point = Math::Point3D(x, y, z);
    const libconfig::Setting &color = setting.lookup("color");

    if (color.isAggregate())
    {
        int red, g, b;
        color.lookupValue("r", red);
        color.lookupValue("g", g);
        color.lookupValue("b", b);
        size_t color = ((size_t)red << 16) | ((size_t)g << 8) | (size_t)b;

        return std::make_shared<Math::Sphere>(point, r, TransformerParser::getTransformer(setting), color);
    }

    return std::make_shared<Math::Sphere>(point, r);
}