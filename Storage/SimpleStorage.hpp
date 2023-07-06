#pragma once

#include <IStorage.hpp>
#include <Lookup.hpp>

namespace Storage {
    class SimpleStorage : public IStorage {
        public:
            SimpleStorage(const RayTracer::Scene&);

            std::optional<RayTracer::RenderingObjectParameters> lookupIntersection(const RayTracer::Ray&) const;
        private:
            RayTracer::ObjectsPtrs objs_ptrs;
    };
}
