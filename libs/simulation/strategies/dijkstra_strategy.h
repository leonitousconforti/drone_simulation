#pragma once

#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/routing/dijkstra.h"
#include "path_strategy.h"

namespace drone_simulation::simulation::movement_strategies {

/**
 * @brief this class inherits from the PathStrategy class and is responsible for
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
  DijkstraStrategy(geometry::Vector3f start, geometry::Vector3f end,
                   const maps::IGraph* graph) {
    using namespace geometry;
    using namespace routing;
    int64_t start_id = graph->nearestNode(start, euclideanDistance)->getId();
    int64_t end_id = graph->nearestNode(end, euclideanDistance)->getId();
    path = Dijkstra::Default().getPath(graph, start_id, end_id);
  }

  void move(IEntity* entity, double dt) {}
  bool isCompleted() { return true; }
};

}  // namespace drone_simulation::simulation::movement_strategies
