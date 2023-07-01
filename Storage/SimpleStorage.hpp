#pragma once

#include <IStorage.hpp>

namespace Storage {
    class SimpleStorage : public IStorage {
        public:
            SimpleStorage(const RayTracer::Scene&);

            const RayTracer::Objects& possibleIntersected(const RayTracer::Ray&) const;

            const RayTracer::Sources& possibleIlluminated(const RayTracer::Ray&) const;

        private:
            const RayTracer::Scene& scene_;
    };
}
