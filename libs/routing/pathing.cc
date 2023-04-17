#include "astar.h"
#include "depth_first_search.h"
#include "dijkstra.h"
#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"

namespace drone_simulation::routing {

std::vector<geometry::Point3f> AStar::getPath(
    const maps::IGraph* graph, const geometry::Point3f& from,
    const geometry::Point3f& to) const {}

std::vector<geometry::Point3f> DepthFirstSearch::getPath(
    const maps::IGraph* graph, const geometry::Point3f& from,
    const geometry::Point3f& to) const {}

}  // namespace drone_simulation::routing
