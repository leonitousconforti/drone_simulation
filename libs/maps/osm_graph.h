#pragma once

#include <memory>
#include <string>

#include "graph.h"

namespace drone_simulation::maps {

std::unique_ptr<IGraph> loadOsmGraph(const std::string& filepath,
                                     const bool prune = true);

};  // namespace drone_simulation::maps
