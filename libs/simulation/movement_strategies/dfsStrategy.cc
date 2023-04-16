#include "dfsStrategy.h"

#include "libs/routing/depth_first_search.h"

namespace drone_simulation::simulation::movement_strategies {

DfsStrategy::DfsStrategy(geometry::Vector3f start, geometry::Vector3f end,
                         const maps::IGraph* graph) {
  path = routing::DepthFirstSearch::Default().getPath(graph, start, end);
}

}  // namespace drone_simulation::simulation::movement_strategies
