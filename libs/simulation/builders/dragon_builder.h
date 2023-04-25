#pragma once

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/entities/dragon.h"

namespace drone_simulation::simulation::builders {

class DragonBuilder : public IBuilder<entities::Dragon> {
  DragonBuilder* addFireBreath() { return this; }
};

}  // namespace drone_simulation::simulation::builders
