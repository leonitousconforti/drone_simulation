#pragma once

#include <vector>

#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "routing_strategy.h"

namespace drone_simulation::routing {

class A_Star : public RoutingStrategy {
 public:
  A_Star()
      : cost(geometry::euclideanDistance),
        heuristic(geometry::euclideanDistance) {}

  A_Star(geometry::DistanceFunction cost, geometry::DistanceFunction heuristic)
      : cost(cost), heuristic(heuristic) {}

  virtual const std::vector<geometry::Point3f> getPath(
      const maps::IGraph* graph, const geometry::Point3f from_location,
      const geometry::Point3f to_location) const;

  static const RoutingStrategy& Default() {
    static A_Star astar;
    return astar;
  }

 private:
  geometry::DistanceFunction cost;
  geometry::DistanceFunction heuristic;
};

}  // namespace drone_simulation::routing
