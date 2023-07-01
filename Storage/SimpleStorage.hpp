#pragma once

#include <IStorage.hpp>
#include <RayTrace.hpp>

namespace Storage {
    class SimpleStorage : public IStorage {
        public:
            SimpleStorage(const RayTracer::Scene&);

            Math::Vector3D ProcessRay(RayTracer::Ray&) const;

        private:
            const RayTracer::Scene& scene_;
    };
}
