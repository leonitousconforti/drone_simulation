#include "draw_map.h"

#include <vector>

#include "libs/geometry/bounding_box.h"
#include "libs/geometry/image.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/maps/graph_node.h"

using namespace drone_simulation;

geometry::Image drawGraph(const maps::IGraph* graph) {
  geometry::BoundingBox bb = graph->getBoundingBox();
  const std::vector<maps::IGraphNode*>& nodes = graph->getNodes();
  float aspectRatio = (bb.max.x - bb.min.x) / (bb.max.y - bb.min.y);

  int resolution = 2048;
  geometry::Image output(resolution, resolution * aspectRatio);
  output.clear({0, 0, 0, 1});

  for (size_t i = 0; i < nodes.size(); i++) {
    geometry::Point3f normalizedPoint = bb.normalize(nodes[i]->getPosition());
    const std::vector<maps::IGraphNode*>& neighbors = nodes[i]->getNeighbors();

    int startX = normalizedPoint.y * output.getWidth();
    int startY = normalizedPoint.x * output.getHeight();
    output.drawPoint(startX, startY, {1, 0.5, 0.5, 1});

    for (size_t j = 0; j < neighbors.size(); j++) {
      geometry::Point3f neighborPos = bb.normalize(neighbors[j]->getPosition());
      int endX = neighborPos.y * output.getWidth();
      int endY = neighborPos.x * output.getHeight();
      output.drawLine(startX, startY, endX, endY, {0.5, 0.5, 1, 1});
    }
  }

  return output;
}
