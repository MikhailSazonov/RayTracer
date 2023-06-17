#include <stdexcept>

#include <Building/Factories/FigureFactory.hpp>
#include <Building/Factories/SourceFactory.hpp>
#include "ConfigBuilder.hpp"


ConfigBuilder::ConfigBuilder(std::string file)
{
    FigureFactory figfactory;
    SourceFactory srcfactory;
    try
    {
        // Read the configuration file
        this->cfg_.readFile(file.c_str());

        // Get settings
        const libconfig::Setting &primitivesSettings = cfg_.lookup("primitives");

        for (const auto &group : primitivesSettings)
        {
            std::string groupName = group.getName();
            for (const auto &figure : group) {
                this->figures_[groupName].push_back(figfactory.build(groupName, figure));
            }
        }

        const libconfig::Setting &lightsSettings = cfg_.lookup("lights");

        for (const auto &group : lightsSettings)
        {
            std::string groupName = group.getName();
            for (const auto &figure : group) {
                this->lights_[groupName].push_back(srcfactory.build(groupName, figure));
            }
        }

        // TODO:
        // Still lacking camera implementation
        // Once theyre completed, come back here and implement parsing of camera specs
        double fieldOfView;
        int w, h;
        const libconfig::Setting &cameraSettings = cfg_.lookup("camera");
        const libconfig::Setting &resolution = cameraSettings.lookup("resolution");
        cameraSettings.lookupValue("fieldOfView", fieldOfView);
        resolution.lookupValue("width", w);
        resolution.lookupValue("height", h);
        this->camera_.reset(new RayTracer::Camera(fieldOfView, {w, h}, TransformerParser::getTransformer(cameraSettings)));
    }
    catch (const libconfig::FileIOException &fioex)
    {
        throw std::runtime_error("Error reading file: " + std::string(fioex.what()));
    }
    catch (const libconfig::ParseException &pex)
    {
        throw std::runtime_error("Parse error at " + std::string(pex.getFile()) + ":" + std::to_string(pex.getLine()) + " - " + pex.getError());
    }
    catch (const libconfig::SettingNotFoundException &nfex)
    {
        throw std::runtime_error("Setting not found: " + std::string(nfex.what()));
    }
}

std::shared_ptr<RayTracer::Camera>& ConfigBuilder::getCamera()
{
    return this->camera_;
}

std::vector<std::shared_ptr<RayTracer::ISource>> ConfigBuilder::getLights()
{
    std::vector<std::shared_ptr<RayTracer::ISource>> allLights;

    for (const auto &pair : this->lights_)
    {
        allLights.insert(allLights.end(), pair.second.begin(), pair.second.end());
    }
    return allLights;
}

std::vector<std::shared_ptr<Math::AFigure>> ConfigBuilder::getFigures()
{
    std::vector<std::shared_ptr<Math::AFigure>> allFigures;

    for (const auto &pair : this->figures_)
    {
        allFigures.insert(allFigures.end(), pair.second.begin(), pair.second.end());
    }
    return allFigures;
}

std::vector<std::shared_ptr<Math::AFigure>> ConfigBuilder::getFigures(std::string group)
{
    if (this->figures_.find(group) == this->figures_.end())
        throw std::runtime_error("Group " + group + " could not be found.");

    return this->figures_[group];
}