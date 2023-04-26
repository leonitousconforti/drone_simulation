#pragma once

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/robot_builder.h"
#include "libs/simulation/entities/robot.h"

namespace drone_simulation::simulation::factories {

class RobotFactory : public IFactory {
 public:
  virtual ~RobotFactory() {}

  std::optional<anyBuilder> createBuilder(const std::string& type) {
    if (type == "robot") {
      return new builders::RobotBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
