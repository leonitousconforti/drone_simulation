#pragma once

#include <memory>
#include <string>
#include <unordered_map>
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

  void addNode(std::shared_ptr<IGraphNode> node);
  const bool contains(const int64_t id) const;
  const std::vector<std::shared_ptr<IGraphNode>>& getNodes() const;
  const std::shared_ptr<IGraphNode> getNodeById(const int64_t id) const;
  void addEdge(const int64_t id1, const int64_t id2);

  void prune();
  const geometry::BoundingBox getBoundingBox() const;
  const std::shared_ptr<IGraphNode> nearestNode(
      const geometry::Point3f point,
      const geometry::DistanceFunction& distance) const;

 private:
  std::vector<std::shared_ptr<IGraphNode>> nodes;
  std::unordered_map<int64_t, std::shared_ptr<IGraphNode>> lookup;
};

}  // namespace drone_simulation::maps
