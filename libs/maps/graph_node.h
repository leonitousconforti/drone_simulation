#pragma once

#include <string>

#include "libs/geometry/point3f.h"

namespace drone_simulation::maps {

class IGraphNode {
 public:
  ~IGraphNode();
  IGraphNode(geometry::Point3f position, const std::string& name);

  const std::string& getName() const;
  const geometry::Point3f getPosition() const;
  const std::vector<IGraphNode*>& getNeighbors() const;
  void addNeighbor(IGraphNode* neighbor);

  friend std::ostream& operator<<(std::ostream& os, const IGraphNode& node);

 private:
  const std::string& name;
  geometry::Point3f position;
  std::vector<IGraphNode*> neighbors;
};

}  // namespace drone_simulation::maps
