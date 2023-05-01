#pragma once

#include "libs/simulation/entities/drone.h"

namespace drone_simulation::simulation::decorators {

class BatteryDecorator : public entities::Drone {
 public:
  BatteryDecorator(const entities::Drone* drone) : drone(drone) {}

  virtual void update(double dt, std::vector<IEntity*> scheduler) {
    this->drone->getId();
    Drone::update(dt, scheduler);
  }

 private:
  const entities::Drone* drone;
};

}  // namespace drone_simulation::simulation::decorators
