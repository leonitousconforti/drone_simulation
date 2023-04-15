#pragma once

#include "graph.h"
#include "pathStrategy.h"

namespace drone_simulation::simulation::movement_strategies {

/**
 * @brief this class inhertis from the PathStrategy class and is responsible for
 * generating the dijkstra path that the drone will take.
 */
class DijkstraStrategy : public PathStrategy {
 public:
  /**
   * @brief Construct a new Astar Strategy object
   *
   * @param position Current position
   * @param destination End destination
   * @param graph Graph/Nodes of the map
   */
  DijkstraStrategy(Vector3 position, Vector3 destination,
                   const routing::IGraph* graph);
};

}  // namespace drone_simulation::simulation::movement_strategies
