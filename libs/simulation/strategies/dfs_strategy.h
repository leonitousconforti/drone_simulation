#pragma once

#include "libs/maps/graph.h"
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
  DfsStrategy(geometry::Vector3f position, geometry::Vector3f destination,
              const maps::IGraph* graph);

  void move(IEntity* entity, double dt);
  bool isCompleted();
};

}  // namespace drone_simulation::simulation::movement_strategies
