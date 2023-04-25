#pragma once

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/entities/human.h"

namespace drone_simulation::simulation::builders {

class HumanBuilder : public IBuilder<entities::Human> {};

}  // namespace drone_simulation::simulation::builders
