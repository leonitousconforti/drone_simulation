#pragma once

#include <optional>

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/IEntity.h"
#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/robot_builder.h"

namespace drone_simulation::simulation::factories {

class RobotFactory : public IFactory {
 public:
  virtual ~RobotFactory() {}

  std::optional<IBuilder<IEntity>*> createBuilder(const std::string& type) {
    if (type == "robot") {
      return (IBuilder<IEntity>*)new builders::RobotBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
