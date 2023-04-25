#include "battery_decorator.h"

#include "libs/simulation/entities/drone.h"

namespace drone_simulation::simulation::decorators {

BatteryDecorator::BatteryDecorator(const entities::Drone* drone)
    : drone(drone) {}

}  // namespace drone_simulation::simulation::decorators
