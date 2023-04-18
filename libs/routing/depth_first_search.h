#pragma once

#include <vector>

#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "routing_strategy.h"

namespace drone_simulation::routing {

class DepthFirstSearch : public RoutingStrategy {
 public:
  virtual ~DepthFirstSearch() {}

  virtual const std::vector<geometry::Point3f> getPath(
      const maps::IGraph* graph, const int64_t from_id,
      const int64_t to_id) const;

  static const RoutingStrategy& Default() {
    static DepthFirstSearch dfs;
    return dfs;
  }
};

}  // namespace drone_simulation::routing
