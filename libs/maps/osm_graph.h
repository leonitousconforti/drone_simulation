#pragma once

#include <string>

#include "graph.h"

namespace drone_simulation::maps {

IGraph* loadOsmGraph(const std::string& filepath, const bool prune = true);

};  // namespace drone_simulation::maps
