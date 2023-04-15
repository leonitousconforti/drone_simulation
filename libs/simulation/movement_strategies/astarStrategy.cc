#include "astarStrategy.h"

#include "libs/routing/astar.h"

namespace drone_simulation::simulation::movement_strategies {

AstarStrategy::AstarStrategy(geometry::Point3f start, geometry::Point3f end,
                             const maps::IGraph* graph) {
  path = routing::AStar::Default().getPath(graph, start, end);
}

}  // namespace drone_simulation::simulation::movement_strategies
