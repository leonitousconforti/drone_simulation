#pragma once

#include <vector>

#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"

namespace drone_simulation::routing {

class RoutingStrategy {
 public:
  virtual ~RoutingStrategy() {}
  virtual const std::vector<geometry::Point3f> getPath(
      const maps::IGraph* graph, const geometry::Point3f from_location,
      const geometry::Point3f to_location) const = 0;
};

}  // namespace drone_simulation::routing
