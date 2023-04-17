#include <iostream>

#include "libs/geometry/bounding_box.h"
#include "libs/geometry/color.h"
#include "libs/geometry/image.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/maps/graph_node.h"
#include "libs/maps/osm_graph.h"

using namespace drone_simulation::geometry;
using namespace drone_simulation::maps;

Image drawGraph(const IGraph* graph) {
  BoundingBox bb = graph->getBoundingBox();
  const std::vector<IGraphNode*>& nodes = graph->getNodes();
  float aspectRatio = (bb.max.x - bb.min.x) / (bb.max.y - bb.min.y);

  int resolution = 1024;
  Image output(resolution, resolution * aspectRatio);
  output.clear(Color{0, 0, 0, 1});

  for (size_t i = 0; i < nodes.size(); i++) {
    Point3f normalizedPoint = bb.normalize(nodes[i]->getPosition());
    const std::vector<IGraphNode*>& neighbors = nodes[i]->getNeighbors();

    int startX = normalizedPoint.y * output.getWidth();
    int startY = normalizedPoint.x * output.getHeight();
    output.drawPoint(startX, startY, Color(1, 0.5, 0.5, 1));

    for (size_t j = 0; j < neighbors.size(); j++) {
      Point3f neighborPos = bb.normalize(neighbors[j]->getPosition());
      int endX = neighborPos.y * output.getWidth();
      int endY = neighborPos.x * output.getHeight();
      output.drawLine(startX, startY, endX, endY, Color(0.5, 0.5, 1, 1));
    }
  }

  return output;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "wrong usage, expected \"map_viewer path/to/map.osm "
                 "path/to/output/folder/\""
              << std::endl;
    return -1;
  }

  IGraph* graph = loadOsmGraph(argv[1], false);
  if (graph == nullptr) {
    std::cout << "Failed to parse graph file" << std::endl;
    return -2;
  }

  Image output1 = drawGraph(graph);
  output1.saveAs(std::string(argv[2]) + "total.png");

  graph->prune();
  Image output2 = drawGraph(graph);
  output2.saveAs(std::string(argv[2]) + "pruned.png");

  delete graph;
  return 0;
}
