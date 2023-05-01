#pragma once

#include <optional>

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/all.h"

namespace drone_simulation::simulation::factories {

class DroneFactory : public IFactory {
 public:
  virtual ~DroneFactory() {}

  std::optional<builders::anyBuilder> createBuilder(const std::string& type) {
    if (type == "drone") {
      return new builders::DroneBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
