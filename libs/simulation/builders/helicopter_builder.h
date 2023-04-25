#pragma once

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/entities/helicopter.h"

namespace drone_simulation::simulation::builders {

class HelicopterBuilder : public IBuilder<entities::Helicopter> {
  HelicopterBuilder* addBlades() { return this; }
};

}  // namespace drone_simulation::simulation::builders
