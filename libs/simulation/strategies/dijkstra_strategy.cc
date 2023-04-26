#include "dijkstra_strategy.h"

#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/routing/dijkstra.h"

namespace drone_simulation::simulation::movement_strategies {

DijkstraStrategy::DijkstraStrategy(geometry::Vector3f start,
                                   geometry::Vector3f end,
                                   const maps::IGraph* graph) {
  int64_t start_id =
      graph->nearestNode(start, geometry::euclideanDistance)->getId();
  int64_t end_id =
      graph->nearestNode(end, geometry::euclideanDistance)->getId();
  path = routing::Dijkstra::Default().getPath(graph, start_id, end_id);
}

void DijkstraStrategy::move(IEntity* entity, double dt) {}
bool DijkstraStrategy::isCompleted() { return true; }

}  // namespace drone_simulation::simulation::movement_strategies
