#pragma once

#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "pathStrategy.h"

namespace drone_simulation::simulation::movement_strategies {

class BeelineStrategy : public PathStrategy {
 public:
  BeelineStrategy(Vector3 pos, Vector3 des)
      : PathStrategy({{pos[0], pos[1], pos[2]}, {des[0], des[1], des[2]}}) {}
};

}  // namespace drone_simulation::simulation::movement_strategies
