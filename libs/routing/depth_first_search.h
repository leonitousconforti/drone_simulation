#pragma once

#include <string>

#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "routing_strategy.h"

namespace drone_simulation::routing {

class DepthFirstSearch : public RoutingStrategy {
 public:
  virtual ~DepthFirstSearch() {}

  std::vector<geometry::Point3f> getPath(const maps::IGraph* graph,
                                         const geometry::Point3f& from,
                                         const geometry::Point3f& to) const;

  static const RoutingStrategy& Default() {
    static DepthFirstSearch dfs;
    return dfs;
  }
};

}  // namespace drone_simulation::routing
