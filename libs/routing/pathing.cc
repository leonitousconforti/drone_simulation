#include <stdexcept>

#include "astar.h"
#include "depth_first_search.h"
#include "dijkstra.h"
#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/geometry/vector3f.h"
#include "libs/maps/graph.h"

namespace drone_simulation::routing {

std::vector<std::string> AStar::getPath(const maps::IGraph* graph,
                                        const geometry::Point3f& from,
                                        const geometry::Point3f& to) const {
  throw std::runtime_error("Not implemented");
}

std::vector<std::string> DepthFirstSearch::getPath(
    const maps::IGraph* graph, const geometry::Point3f& from,
    const geometry::Point3f& to) const {
  throw std::runtime_error("Not implemented");
}

}  // namespace drone_simulation::routing
