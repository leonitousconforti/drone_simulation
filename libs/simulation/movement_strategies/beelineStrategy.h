#pragma once

#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "pathStrategy.h"

namespace drone_simulation::simulation::movement_strategies {

class BeelineStrategy : public PathStrategy {
 public:
  BeelineStrategy(geometry::Vector3f start, geometry::Vector3f end);
};

}  // namespace drone_simulation::simulation::movement_strategies
