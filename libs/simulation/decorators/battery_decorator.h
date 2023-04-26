#pragma once

#include "libs/simulation/entities/drone.h"

namespace drone_simulation::simulation::decorators {

class BatteryDecorator : public entities::Drone {
 public:
  BatteryDecorator(const entities::Drone* drone);

  virtual void update(double dt, std::vector<IEntity*> scheduler);

 private:
  const entities::Drone* drone;
};

}  // namespace drone_simulation::simulation::decorators
