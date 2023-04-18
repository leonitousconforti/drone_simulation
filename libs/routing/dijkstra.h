#pragma once

#include "astar.h"
#include "libs/geometry/distance_function.h"
#include "routing_strategy.h"

namespace drone_simulation::routing {

class Dijkstra : public A_Star {
 public:
  virtual ~Dijkstra() {}
  Dijkstra()
      : A_Star(geometry::euclideanDistance, geometry::euclideanDistance) {}

  static const RoutingStrategy& Default() {
    static Dijkstra dikjstra;
    return dikjstra;
  }
};

}  // namespace drone_simulation::routing
