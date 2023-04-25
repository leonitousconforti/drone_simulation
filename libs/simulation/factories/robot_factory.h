#pragma once

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/robot_builder.h"
#include "libs/simulation/entities/robot.h"

namespace drone_simulation::simulation::factories {

class RobotFactory : public IFactory {
 public:
  virtual ~RobotFactory() {}

  anyBuilder createBuilder(const std::string& type) {
    if (type == "robot") {
      return new builders::DroneBuilder();
    }

    return {};
  }
};

}  // namespace drone_simulation::simulation::factories
