#include <iostream>
#include <memory>
#include <vector>

#include "libs/geometry/bounding_box.h"
#include "libs/geometry/image.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/maps/graph_node.h"
#include "libs/maps/osm_graph.h"
#include "libs/routing/astar.h"
#include "libs/routing/depth_first_search.h"
#include "libs/routing/dijkstra.h"

using namespace std;
using namespace drone_simulation::geometry;
using namespace drone_simulation::maps;
using namespace drone_simulation::routing;

void drawPath(Image& image, const BoundingBox& bb, const vector<Point3f>& path,
              const Color color) {
  for (size_t i = 1; i < path.size(); i++) {
    const Point3f normalized_pos1 = bb.normalize(path[i - 1]);
    const Point3f normalized_pos2 = bb.normalize(path[i]);
    int start_x = normalized_pos1.y * image.getWidth();
    int start_y = normalized_pos1.x * image.getHeight();
    int end_x = normalized_pos2.y * image.getWidth();
    int end_y = normalized_pos2.x * image.getHeight();
    image.drawLine(start_x, start_y, end_x, end_y, color);
  }
}

Image drawGraph(const IGraph* graph) {
  BoundingBox bb = graph->getBoundingBox();
  const auto nodes = graph->getNodes();
  float aspectRatio = (bb.max.x - bb.min.x) / (bb.max.y - bb.min.y);

  int resolution = 2048;
  Image output(resolution, resolution * aspectRatio);
  output.clear({0, 0, 0, 1});

  for (size_t i = 0; i < nodes.size(); i++) {
    Point3f normalizedPoint = bb.normalize(nodes[i]->getPosition());
    const auto& neighbors = nodes[i]->getNeighbors();

    int startX = normalizedPoint.y * output.getWidth();
    int startY = normalizedPoint.x * output.getHeight();
    output.drawPoint(startX, startY, {1, 0.5, 0.5, 1});

    for (size_t j = 0; j < neighbors.size(); j++) {
      Point3f neighborPos = bb.normalize(neighbors[j]->getPosition());
      int endX = neighborPos.y * output.getWidth();
      int endY = neighborPos.x * output.getHeight();
      output.drawLine(startX, startY, endX, endY, {0.5, 0.5, 1, 1});
    }
  }

  return output;
}

int main(int argc, char* argv[]) {
  if (argc != 3) {
    cerr << "wrong usage, expected \"map_viewer path/to/map.osm "
            "path/to/output/folder/\""
         << endl;
    return -1;
  }

  IGraph* graph = loadOsmGraph(argv[1], false).get();
  if (graph == nullptr) {
    cerr << "Failed to parse graph file" << endl;
    return -2;
  }

  Image output1 = drawGraph(graph);
  output1.saveAs(string(argv[2]) + "total.png");

  graph->prune();
  Image output2 = drawGraph(graph);
  output2.saveAs(string(argv[2]) + "pruned.png");

  BoundingBox bb = graph->getBoundingBox();
  int64_t start = graph->nearestNode(bb.min, euclideanDistance)->getId();
  int64_t end = graph->nearestNode(bb.max, euclideanDistance)->getId();

  const vector<Point3f> a_star_path =
      A_Star::Default().getPath(graph, start, end);
  const vector<Point3f> dijkstra_path =
      Dijkstra::Default().getPath(graph, start, end);
  const vector<Point3f> dfs_path =
      DepthFirstSearch::Default().getPath(graph, start, end);

  Image base_image = drawGraph(graph);
  drawPath(base_image, bb, dfs_path, {1, 0, 0, 1});
  drawPath(base_image, bb, a_star_path, {0, 1, 0, 1});
  drawPath(base_image, bb, dijkstra_path, {1, 0.5, 0, 1});
  base_image.saveAs(string(argv[2]) + "routes.png");

  return 0;
}
