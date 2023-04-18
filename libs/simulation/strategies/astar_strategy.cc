#include "astar_strategy.h"

#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/routing/astar.h"

namespace drone_simulation::simulation::movement_strategies {

AstarStrategy::AstarStrategy(geometry::Point3f start, geometry::Point3f end,
                             const maps::IGraph* graph) {
  int64_t start_id =
      graph->nearestNode(start, geometry::euclideanDistance)->getId();
  int64_t end_id =
      graph->nearestNode(end, geometry::euclideanDistance)->getId();
  path = routing::A_Star::Default().getPath(graph, start_id, end_id);
}

}  // namespace drone_simulation::simulation::movement_strategies
