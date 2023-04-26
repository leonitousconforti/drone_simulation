#include "battery_decorator.h"

#include "libs/simulation/entities/drone.h"

namespace drone_simulation::simulation::decorators {

BatteryDecorator::BatteryDecorator(const entities::Drone* drone)
    : drone(drone) {}

void BatteryDecorator::update(double dt, std::vector<IEntity*> scheduler) {
  this->drone->getId();
  Drone::update(dt, scheduler);
}

}  // namespace drone_simulation::simulation::decorators
