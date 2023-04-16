#pragma once

#include "libs/maps/graph.h"
#include "pathStrategy.h"

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
};

}  // namespace drone_simulation::simulation::movement_strategies
