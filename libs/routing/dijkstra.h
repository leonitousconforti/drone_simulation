#pragma once

#include "astar.h"
#include "libs/geometry/distance_function.h"
#include "routing_strategy.h"

namespace drone_simulation::routing {

class Dijkstra : public AStar {
 public:
  virtual ~Dijkstra() {}
  Dijkstra()
      : AStar(geometry::euclideanDistance, geometry::euclideanDistance) {}

  static const RoutingStrategy& Instance() {
    static Dijkstra dikjstra;
    return dikjstra;
  }
};

}  // namespace drone_simulation::routing
