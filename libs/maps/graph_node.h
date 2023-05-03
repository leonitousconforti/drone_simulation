#pragma once

#include <memory>

#include "libs/geometry/point3f.h"

namespace drone_simulation::maps {

class IGraphNode {
 public:
  ~IGraphNode();
  IGraphNode(geometry::Point3f position, const int64_t id);

  const int64_t getId() const;
  const geometry::Point3f getPosition() const;
  const std::vector<std::shared_ptr<IGraphNode>>& getNeighbors() const;
  void addNeighbor(std::shared_ptr<IGraphNode> neighbor);

  friend std::ostream& operator<<(std::ostream& os, const IGraphNode& node);

 private:
  const int64_t id;
  geometry::Point3f position;
  std::vector<std::shared_ptr<IGraphNode>> neighbors;
};

}  // namespace drone_simulation::maps
