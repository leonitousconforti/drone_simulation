#pragma once

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

  void addNode(IGraphNode* node);
  bool contains(std::string& name) const;
  const std::vector<IGraphNode*>& getNodes() const;
  IGraphNode* getNodeByName(std::string& name) const;
  void addEdge(std::string& name1, std::string& name2);

  void prune();
  const geometry::BoundingBox getBoundingBox() const;
  const IGraphNode* nearestNode(
      geometry::Point3f point,
      const geometry::DistanceFunction& distance) const;

 private:
  std::vector<IGraphNode*> nodes;
  std::unordered_map<std::string, IGraphNode*> lookup;
};

}  // namespace drone_simulation::maps
