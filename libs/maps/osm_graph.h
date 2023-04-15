#pragma once

#include <string>

#include "graph.h"

namespace drone_simulation::maps {

IGraph* loadOsmGraph(const std::string& filepath);

};  // namespace drone_simulation::maps
