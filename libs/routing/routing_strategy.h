#pragma once

#include <vector>

#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"

namespace drone_simulation::routing {

class RoutingStrategy {
 public:
  virtual ~RoutingStrategy() {}
  virtual const std::vector<geometry::Point3f> getPath(
      const maps::IGraph* graph, const int64_t from_id,
      const int64_t to_id) const = 0;
};

}  // namespace drone_simulation::routing
