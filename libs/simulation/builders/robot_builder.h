#pragma once

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/entities/robot.h"

namespace drone_simulation::simulation::builders {

class RobotBuilder : public IBuilder<entities::Robot> {};

}  // namespace drone_simulation::simulation::builders
