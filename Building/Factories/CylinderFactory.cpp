#include "CylinderFactory.hpp"

CylinderFactory::CylinderFactory(){};

CylinderFactory::~CylinderFactory(){};

std::shared_ptr<Math::AFigure> CylinderFactory::createFigure(const libconfig::Setting &setting)
{
    int x, y, z;
    double r, s;
    std::optional<double> h(std::nullopt);

    const libconfig::Setting &color = setting.lookup("color");
    const libconfig::Setting &center = setting.lookup("center");

    setting.lookupValue("radius", r);
    if (setting.exists("height")) {
        double height;
        setting.lookupValue("height", height);
        h = height;
    }
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

        return std::make_shared<Math::Cylinder>(center_p, r, h, TransformerParser::getTransformer(setting), color_s, s);
    }

    return std::make_shared<Math::Cylinder>(center_p, r, h);
}
