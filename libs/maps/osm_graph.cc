#include "osm_graph.h"

#include <exception>
#include <iostream>

#include "osmium/handler.hpp"
#include "osmium/io/xml_input.hpp"
#include "osmium/visitor.hpp"

namespace drone_simulation::maps {

IGraph* loadOsmGraph(const std::string& filepath) {
  IGraph* graph = new IGraph();

  try {
    // Initialize the reader with the filename from the command line and tell it
    // to only read nodes, ways, and relations
    osmium::io::Reader reader{filepath, osmium::osm_entity_bits::node};

    // Apply a lambda function to the data to make our graph
    osmium::apply(reader, [&](const osmium::Node& node) {
      float lat = node.location().lat();
      float lon = node.location().lon();
      osmium::object_id_type id = node.id();
      IGraphNode* graphNode = new IGraphNode({lat, lon, 0}, std::to_string(id));
      graph->addNode(graphNode);
    });

    // You do not have to close the Reader explicitly, but because the
    // destructor can't throw, you will not see any errors otherwise.
    reader.close();
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
