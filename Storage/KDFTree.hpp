#pragma once

#include <KDFTreeUtils.hpp>
#include <IStorage.hpp>
#include <Lookup.hpp>

#include <random>
#include <ctime>

namespace Storage {
    // KD Tree for storing the objects.
    // The differences from classic KD Tree:
    // 1. Marginal nodes are infinite to at least one side
    // 2. Structure is flattened, so each node does not contains up to 2 ^ 3 nodes,
    // but each node contain 2 nodes, splitted with, for example, X axis,
    // their nodes are spliited recursively, but now with Y axis, etc. After Z axis we start
    // from the beginning (X in that case)
    // The order of choosing the cutting axis seems not to have effect,
    // anyway it is defined it KDFTreeUtils.hpp
    // Number of nodes and complexity remains the same, but it is easier to write and
    // understand the code.
    //
    // Stopping criteria on creating children are:
    // 1. The depth of recursion == MAX_TREE_DEPTH
    // 2. Number of objects in current node <= MIN_OBJECTS_IN_NODE
    class KDFTree : public IStorage {
        public:
            KDFTree(const RayTracer::Scene& scene);

            std::optional<RayTracer::RenderingObjectParameters> lookupIntersection(const RayTracer::Ray&) const;

        private:
            // BUILDING

            void InitHead(const RayTracer::Scene& scene);

            void CreateChildren(std::shared_ptr<Detail::KDFTreeNode>& node, size_t dividing_axis_index = 0, size_t recursion_depth = 0);

            double PickDividingValue(const RayTracer::ObjectsPtrs& obj_refs, Detail::CuttingAxis dividing_axis);

            // Returns LEFT, if all points from figure box < dividing axis, RIGHT if all points > diving axis,
            // BOTH if none of those
            Detail::NodeBelonging DetermineBelonging(const Math::AFigure& figure, Detail::CuttingAxis dividing_axis, double dividing_value);

            Detail::NodeBelonging CompareThePoints(Math::Point3D* points, int index, double dividing_value);

            // WORKING WITH RAYS

            void traverseDown(const RayTracer::Ray&, const Math::Point3D&, const std::shared_ptr<Detail::KDFTreeNode>**,
            Detail::ContainingCube&, std::optional<RayTracer::RenderingObjectParameters>&, bool) const;

            void traverseUp(const Math::Point3D&, const std::shared_ptr<Detail::KDFTreeNode>**, Detail::ContainingCube&) const;

            double transitionToNextNode(const RayTracer::Ray&, const Detail::ContainingCube&) const;

        private:
            std::shared_ptr<Detail::KDFTreeNode> head_;
            const RayTracer::Sources& sources_;
            std::mt19937 gen;
    };
}
