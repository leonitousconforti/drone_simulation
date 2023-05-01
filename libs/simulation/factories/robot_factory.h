#pragma once

#include <optional>

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/all.h"

namespace drone_simulation::simulation::factories {

class RobotFactory : public IFactory {
 public:
  virtual ~RobotFactory() {}

  std::optional<builders::anyBuilder> createBuilder(const std::string& type) {
    if (type == "robot") {
      return new builders::RobotBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
