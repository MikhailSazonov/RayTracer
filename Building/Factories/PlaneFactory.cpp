#include "PlaneFactory.hpp"

PlaneFactory::PlaneFactory(){};

PlaneFactory::~PlaneFactory(){};

std::shared_ptr<Math::AFigure> PlaneFactory::createFigure(const libconfig::Setting &setting)
{
    const libconfig::Setting &color = setting.lookup("color");

    if (color.isAggregate())
    {
        int red, g, b;
        color.lookupValue("r", red);
        color.lookupValue("g", g);
        color.lookupValue("b", b);
        size_t color = ((size_t)red << 16) | ((size_t)g << 8) | (size_t)b;

        return std::make_shared<Math::Plane>(TransformerParser::getTransformer(setting), color);
    }

    return std::make_shared<Math::Plane>();
}
