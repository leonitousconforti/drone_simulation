#pragma once

#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/routing/depth_first_search.h"
#include "path_strategy.h"

namespace drone_simulation::simulation::movement_strategies {

/**
 * @brief this class inherits from the PathStrategy class and is responsible for
 * generating the depth first search path that the drone will take.
 */
class DfsStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Astar Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  DfsStrategy(const geometry::Vector3f start, const geometry::Vector3f end,
              const maps::IGraph* graph) {
    path = routing::DepthFirstSearch::Default().getPath(graph, start, end);
  }

  void move(IEntity* entity, double dt) {}
  bool isCompleted() { return true; }
};

}  // namespace drone_simulation::simulation::movement_strategies
