#include "dijkstraStrategy.h"

#include "libs/routing/dijkstra.h"

namespace drone_simulation::simulation::movement_strategies {

DijkstraStrategy::DijkstraStrategy(geometry::Vector3f start,
                                   geometry::Vector3f end,
                                   const maps::IGraph* graph) {
  path = routing::Dijkstra::Default().getPath(graph, start, end);
}

}  // namespace drone_simulation::simulation::movement_strategies
