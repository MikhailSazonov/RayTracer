#pragma once

#include <unordered_map>
#include <vector>
#include <libconfig.h++>

#include <Building/Camera/Camera.hpp>
#include <Math/Figures/AFigure.hpp>
#include <Raytracing/Illumination/LightSources/ISource.hpp>

#include <Building/TransformerParser/TransformerParser.hpp>

class ConfigBuilder
{
private:
    libconfig::Config cfg_;                                                                    //! < The config file
    std::shared_ptr<RayTracer::Camera> camera_;                                                //! < The camera
    std::unordered_map<std::string, std::vector<std::shared_ptr<Math::AFigure>>> figures_;     //! < The figures
    std::unordered_map<std::string, std::vector<std::shared_ptr<RayTracer::ISource>>> lights_; //! < The lights

public:
    /**
     * @brief Construct a new Config Builder object
     *
     * This is the parcer class for the programe
     *
     * @param file The path to the config file
     */
    ConfigBuilder(std::string);
    // ~ConfigBuilder();

    std::shared_ptr<RayTracer::Camera> &getCamera();                     //! < Get the camera
    std::vector<std::shared_ptr<RayTracer::ISource>> getLights();        //! < Get the lights
    std::vector<std::shared_ptr<Math::AFigure>> getFigures();            //! < Get the figures
    std::vector<std::shared_ptr<Math::AFigure>> getFigures(std::string); //! < Get the figures in a group
};
