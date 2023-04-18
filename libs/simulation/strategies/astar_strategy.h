#pragma once

#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "path_strategy.h"

namespace drone_simulation::simulation::movement_strategies {

/**
 * @brief this class inherits from the PathStrategy class and is responsible for
 * generating the astar path that the drone will take.
 */
class AstarStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Astar Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  AstarStrategy(geometry::Point3f position, geometry::Point3f destination,
                const maps::IGraph* graph);
};

}  // namespace drone_simulation::simulation::movement_strategies
