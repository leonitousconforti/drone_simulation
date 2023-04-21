#include "osm_graph.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <exception>
#include <iostream>

#include "osmium/handler.hpp"
#include "osmium/io/xml_input.hpp"
#include "osmium/visitor.hpp"

namespace drone_simulation::maps {

// Helpful reference https://wiki.openstreetmap.org/wiki/Elements
IGraph* loadOsmGraph(const std::string& filepath, const bool prune) {
  IGraph* graph = new IGraph();

  try {
    // Only read the node and the way data entries
    osmium::osm_entity_bits::type read_types =
        osmium::osm_entity_bits::node | osmium::osm_entity_bits::way;
    osmium::io::Reader reader{filepath, read_types};

    // The file header can contain metadata such as the program that generated
    // the file and the bounding box of the data.
    osmium::io::Header header = reader.header();
    osmium::Box bounding_box = header.boxes()[0];
    float min_lat = bounding_box.top();
    float min_lon = bounding_box.left();
    float max_lat = bounding_box.bottom();
    float max_lon = bounding_box.right();
    float center_lat = min_lat + (max_lat - min_lat) / 2.0;
    float center_lon = min_lon + (max_lon - min_lon) / 2.0;

    // Lambda function that adds a node to the graph
    auto node_handler = [&](const osmium::Node& node) {
      int64_t id = node.id();
      float lat_diff = node.location().lat() - center_lat;
      float lon_diff = node.location().lon() - center_lon;

      float center_lat_rads = center_lat * M_PI / 180.0;
      float lon = lon_diff * 40075160 * std::cos(center_lat_rads) / 360.0f;
      float lat = -lat_diff * 40008000.0 / 360.0;

      IGraphNode* graphNode = new IGraphNode({lat, lon, 0}, id);
      graph->addNode(graphNode);
    };

    // Lambda function that takes a way and computes the adjacency lists
    auto way_handler = [&](const osmium::Way& way) {
      if (way.tags().has_key("highway"))
        for (size_t i = 1; i < way.nodes().size(); i++) {
          int64_t from = way.nodes()[i - 1].ref();
          int64_t to = way.nodes()[i].ref();
          graph->addEdge(from, to);
        }
    };

    // Apply our lambda functions (in this order) to create the graph
    osmium::apply(reader, node_handler, way_handler);

    // You do not have to close the Reader explicitly, but because the
    // destructor can't throw, you will not see any errors otherwise.
    reader.close();

    // Prune the graph (remove all nodes with no neighbors)
    if (prune) graph->prune();
    return graph;
  }

  // Catch any errors, making sure to cleanup
  catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    delete graph;
    return nullptr;
  }
}

};  // namespace drone_simulation::maps
