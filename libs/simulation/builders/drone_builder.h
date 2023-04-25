#pragma once

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/entities/drone.h"

namespace drone_simulation::simulation::builders {

class DroneBuilder : public IBuilder<entities::Drone> {};

}  // namespace drone_simulation::simulation::builders
