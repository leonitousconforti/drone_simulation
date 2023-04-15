#include <iostream>

#include "image.h"
#include "libs/geometry/bounding_box.h"
#include "libs/geometry/color.h"
#include "libs/maps/graph.h"
#include "libs/maps/osm_graph.h"

using namespace drone_simulation::geometry;
using namespace drone_simulation::maps;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "wrong usage, expected \"map_viewer <path/to/map.osm> "
                 "<path/to/output/image.png>\""
              << std::endl;
    return -1;
  }

  const IGraph* graph = loadOsmGraph(argv[1]);
  if (graph == nullptr) {
    std::cout << "Failed to parse graph file" << std::endl;
    return -2;
  }

  BoundingBox bb = graph->getBoundingBox();
  const std::vector<IGraphNode*>& nodes = graph->getNodes();
  float aspectRatio = (bb.max[1] - bb.min[1]) / (bb.max[0] - bb.min[0]);

  int resolution = 1024;
  Image output(resolution, resolution * aspectRatio);
  output.clear(Color{0, 0, 0, 1});

  for (size_t i = 0; i < nodes.size(); i++) {
    std::vector<float> normalizedPoint =
        bb.Normalize(nodes[i]->getPosition().toVec());
    const std::vector<IGraphNode*>& neighbors = nodes[i]->getNeighbors();

    for (size_t j = 0; j < neighbors.size(); j++) {
      std::vector<float> neighborPos =
          bb.Normalize(neighbors[j]->getPosition().toVec());
      int startX = normalizedPoint[0] * output.getWidth();
      int startY = normalizedPoint[1] * output.getHeight();
      int endX = neighborPos[0] * output.getWidth();
      int endY = neighborPos[1] * output.getHeight();
      output.drawLine(startX, startY, endX, endY, Color(0.5, 0.5, 1, 1));
    }
  }

  output.saveAs(argv[2]);
  delete graph;
  return 0;
}
