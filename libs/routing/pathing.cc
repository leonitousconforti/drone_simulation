#include <memory>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "astar.h"
#include "depth_first_search.h"
#include "dijkstra.h"
#include "libs/geometry/distance_function.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/maps/graph_node.h"

namespace drone_simulation::routing {

// Helper function to transform a list of nodes into a list of positions
const std::vector<geometry::Point3f> nodesToPoints(
    const std::vector<std::shared_ptr<maps::IGraphNode>> nodePath) {
  std::vector<geometry::Point3f> pointPath;
  for (auto node : nodePath) pointPath.emplace_back(node->getPosition());
  return pointPath;
}

// https://en.wikipedia.org/wiki/A*_search_algorithm
const std::vector<geometry::Point3f> A_Star::getPath(
    const maps::IGraph* graph, const geometry::Point3f from_location,
    const geometry::Point3f to_location) const {
  // Grab some important nodes
  std::shared_ptr<maps::IGraphNode> start = graph->nearestNode(from_location);
  std::shared_ptr<maps::IGraphNode> end = graph->nearestNode(to_location);

  // Initially, only the start node is known.
  std::priority_queue<std::shared_ptr<maps::IGraphNode>> openSet;
  openSet.push(start);

  // For node n, cameFrom[n] is the node immediately preceding it on the
  // cheapest path from the start to n currently known
  std::unordered_map<maps::IGraphNode*, maps::IGraphNode*> cameFrom;

  // For node n, gScore[n] is the cost of the cheapest path from start to n
  // currently known.
  std::unordered_map<int64_t, float> gScore;
  gScore[start->getId()] = 0;

  // For node n, fScore[n] := gScore[n] + h(n). fScore[n] represents our current
  // best guess as to how cheap a path could be from start to finish if it goes
  // through n.
  std::unordered_map<int64_t, float> fScore;
  fScore[start->getId()] = geometry::euclideanDistance(
      start->getPosition().toVec(), end->getPosition().toVec());

  // Return an empty vector if no path is found
  return {};
}

// https://en.wikipedia.org/wiki/Depth-first_search
const std::vector<geometry::Point3f> DepthFirstSearch::getPath(
    const maps::IGraph* graph, const geometry::Point3f from_location,
    const geometry::Point3f to_location) const {
  // Grab the important nodes
  std::shared_ptr<maps::IGraphNode> start = graph->nearestNode(from_location);
  std::shared_ptr<maps::IGraphNode> end = graph->nearestNode(to_location);

  // Initialize data structures
  std::unordered_set<int64_t> visited({start->getId()});
  std::queue<std::vector<std::shared_ptr<maps::IGraphNode>>> queue({{start}});

  // Traverse the graph
  while (!queue.empty()) {
    // Get the first path from the queue
    std::vector<std::shared_ptr<maps::IGraphNode>> path = queue.front();
    queue.pop();

    // Get the last node from the path
    std::shared_ptr<maps::IGraphNode> node = path.back();

    // If we made it to the end, transform the nodes to points
    if (node == end) {
      return nodesToPoints(path);
    }

    // Enumerate all adjacent nodes, constructing a new path for each and
    // pushing it into the queue
    for (std::shared_ptr<maps::IGraphNode> neighbor :
         node.get()->getNeighbors())
      if (visited.find(neighbor->getId()) == visited.end()) {
        visited.insert(neighbor->getId());
        std::vector<std::shared_ptr<maps::IGraphNode>> newPath(path);
        newPath.push_back(neighbor);
        queue.push(newPath);
      }
  }

  // Return an empty vector if no path is found
  return {};
}

}  // namespace drone_simulation::routing
