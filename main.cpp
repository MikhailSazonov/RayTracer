#include <Illumination/Ray.hpp>
#include <Illumination/LightSources/DirectIllumination.hpp>
#include <Illumination/LightSources/AmbientIllumination.hpp>

#include <RayTrace.hpp>

#include <Camera/Camera.hpp>

#include <Figures/Cylinder.hpp>
#include <Figures/Cone.hpp>
#include <Figures/Sphere.hpp>
#include <Figures/Plane.hpp>

#include <Transformers/RotationTransformers/RotationTransformerX.hpp>
#include <Transformers/RotationTransformers/RotationTransformerZ.hpp>
#include <Transformers/RotationTransformers/RotationTransformerY.hpp>
#include <Transformers/ScalingTransformer.hpp>

#include <FileUtils/PPMManager.hpp>
#include <Slicer/Slicer.hpp>
#include <ThreadPool/ThreadPool.hpp>
#include <Building/ConfigBuilder/ConfigBuilder.hpp>

#include <Storage.hpp>

#include <CmdLineParser.hpp>

#include <iostream>

void CalcPixel(size_t i, size_t j, size_t width, size_t height, Files::PPMManager& writer, const RayTracer::Camera& cam, const Storage::Storage& storage) {
    double v = i / (double)width;
    double u = j / (double)height;

    if (Settings::isFast()) {
        RayTracer::Ray r = cam.ray(u, v);
        writer[j][i] = RayTracer::convertToRGB(storage.ProcessRay(r));
    } else {
        static const double dv[] = {1.0 / (4.0 * (double)width), 1.0 / (4.0 * (double)width), -1.0 / (4.0 * (double)width), -1.0 / (4.0 * (double)width)};
        static const double du[] = {1.0 / (4.0 * (double)height), -1.0 / (4.0 * (double)height), -1.0 / (4.0 * (double)height), 1.0 / (4.0 * (double)height)};

        Math::Vector3D res;
        for (int k = 0; k < 4; ++k) {
            RayTracer::Ray r = cam.ray(std::clamp(u + du[k], 0., 1.), std::clamp(v + dv[k], 0., 1.));
            res += storage.ProcessRay(r);
        }
        writer[j][i] = RayTracer::convertToRGB(res / 4.0);
    }
}

int main(int argc, char **argv) {
    std::string filename = "result.ppm";
    std::string config_filename = "config.cfg";

    Settings::CmdLineParser::Parse(argc, argv, filename, config_filename);

    ConfigBuilder builder(config_filename);

    RayTracer::Scene scene;

    scene.objects_ = builder.getFigures();
    scene.lights_ = builder.getLights();
    Storage::Storage storage(scene);

    auto& cam = builder.getCamera();

    Files::PPMManager writer(filename, cam->getWidth(), cam->getHeight(), Files::Method::DUMP);
    auto thread_count = std::thread::hardware_concurrency();
    Executors::ThreadPool tp(thread_count);
    std::vector<size_t> slice_params = RayTracer::Slicer::Slice(cam->getWidth(), cam->getHeight(), thread_count);
    auto x_ = cam->getWidth() / slice_params[0];
    auto y_ = cam->getHeight() / slice_params[1];
    tp.Start();
    for (size_t i = 0; i < slice_params[0]; ++i) {
        for (size_t j = 0; j < slice_params[1]; ++j) {
            tp.Submit([&, i, j]() mutable {
                for (size_t k = 0; k < x_; ++k) {
                    for (size_t t = 0; t < y_; ++t) {
                        CalcPixel(i * x_ + k, j * y_ + t, cam->getWidth(), cam->getHeight(), writer, *cam, storage);
                    }
                }
            });
        }
    }
    tp.WaitIdle();
    tp.Stop();
}
