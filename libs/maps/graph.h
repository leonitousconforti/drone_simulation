#pragma once

#include <memory>
#include <vector>

#include "graph_node.h"
#include "libs/geometry/bounding_box.h"
#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"

namespace drone_simulation::maps {

class IGraph {
 public:
  IGraph();
  ~IGraph();

  void addEdge(const int64_t id1, const int64_t id2);
  void addNode(const int64_t id, const geometry::Point3f pos);
  const std::vector<std::shared_ptr<IGraphNode>>& getNodes() const;

  void prune();
  const geometry::BoundingBox getBoundingBox() const;
  const std::shared_ptr<IGraphNode> nearestNode(
      const geometry::Point3f point,
      const geometry::DistanceFunction& distance =
          geometry::euclideanDistance) const;

 private:
  std::vector<std::shared_ptr<IGraphNode>> nodes;
};

}  // namespace drone_simulation::maps
