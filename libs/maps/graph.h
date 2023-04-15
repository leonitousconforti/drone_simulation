#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include "libs/geometry/bounding_box.h"
#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"

namespace drone_simulation::maps {

class IGraphNode {
 public:
  ~IGraphNode();
  IGraphNode(geometry::Point3f position, const std::string& name);

  const std::string& getName() const;
  const std::vector<IGraphNode*>& getNeighbors() const;
  const geometry::Point3f getPosition() const;
  void addNeighbor(IGraphNode* neighbor);

 protected:
  const std::string& name;
  std::vector<IGraphNode*> neighbors;
  geometry::Point3f position;
};

class IGraph {
 public:
  IGraph();
  ~IGraph();

  void addNode(IGraphNode* node);
  bool contains(std::string& name) const;
  IGraphNode* nodeNamed(std::string& name) const;
  const std::vector<IGraphNode*>& getNodes() const;
  void addEdge(std::string& name1, std::string& name2);

  const geometry::BoundingBox getBoundingBox() const;
  const IGraphNode* nearestNode(
      geometry::Point3f point,
      const geometry::DistanceFunction& distance) const;

 protected:
  std::vector<IGraphNode*> nodes;
  std::unordered_map<std::string, IGraphNode*> lookup;
};

}  // namespace drone_simulation::maps
