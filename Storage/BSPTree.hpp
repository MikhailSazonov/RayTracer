#pragma once

#include <BSPTreeUtils.hpp>
#include <IStorage.hpp>
#include <Lookup.hpp>

#include <random>
#include <ctime>

namespace Storage {
    // BSP Tree for storing the objects.

    // Stopping criteria on creating children are:
    // 1. The depth of recursion == MAX_TREE_DEPTH
    // 2. Number of objects in current node <= MIN_OBJECTS_IN_NODE
    class BSPTree : public IStorage {
        public:
            BSPTree(const RayTracer::Scene& scene);

            std::optional<RayTracer::RenderingObjectParameters> lookupIntersection(const RayTracer::Ray&) const;

        private:
            // BUILDING

            void InitHead(const RayTracer::Scene& scene);

            void CreateChildren(std::shared_ptr<Detail::BSPTreeNode>& node, size_t dividing_axis_index = 0, size_t recursion_depth = 0);

            double PickDividingValue(const RayTracer::ObjectsPtrs& obj_refs, Detail::CuttingAxis dividing_axis);

            // Returns LEFT, if all points from figure box < dividing axis, RIGHT if all points > diving axis,
            // BOTH if none of those
            Detail::NodeBelonging DetermineBelonging(const Math::AFigure& figure, Detail::CuttingAxis dividing_axis, double dividing_value);

            Detail::NodeBelonging CompareThePoints(Math::Point3D* points, int index, double dividing_value);

            // WORKING WITH RAYS

            void traverseDown(const RayTracer::Ray&, const Math::Point3D&, const std::shared_ptr<Detail::BSPTreeNode>**,
            Detail::ContainingCube&, std::optional<RayTracer::RenderingObjectParameters>&, bool) const;

            void traverseUp(const Math::Point3D&, const std::shared_ptr<Detail::BSPTreeNode>**, Detail::ContainingCube&) const;

            double transitionToNextNode(const RayTracer::Ray&, const Detail::ContainingCube&) const;

        private:
            std::shared_ptr<Detail::BSPTreeNode> head_;
            const RayTracer::Sources& sources_;
            std::mt19937 gen;
    };
}
