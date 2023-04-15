#pragma once

#include <string>

#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "routing_strategy.h"

namespace drone_simulation::routing {

class AStar : public RoutingStrategy {
 public:
  AStar()
      : cost(geometry::euclideanDistance),
        heuristic(geometry::euclideanDistance) {}

  AStar(geometry::DistanceFunction cost, geometry::DistanceFunction heuristic)
      : cost(cost), heuristic(heuristic) {}

  std::vector<geometry::Point3f> getPath(const maps::IGraph* graph,
                                         const geometry::Point3f& from,
                                         const geometry::Point3f& to) const;

  static const RoutingStrategy& Default() {
    static AStar astar;
    return astar;
  }

 private:
  geometry::DistanceFunction cost;
  geometry::DistanceFunction heuristic;
};

}  // namespace drone_simulation::routing
