#include <iostream>

#include "draw_map.h"
#include "libs/geometry/image.h"
#include "libs/maps/graph.h"
#include "libs/maps/osm_graph.h"

using namespace drone_simulation::geometry;
using namespace drone_simulation::maps;

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "wrong usage, expected \"map_viewer path/to/map.osm "
                 "path/to/output/folder/\""
              << std::endl;
    return -1;
  }

  IGraph* graph = loadOsmGraph(argv[1], false);
  if (graph == nullptr) {
    std::cerr << "Failed to parse graph file" << std::endl;
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
