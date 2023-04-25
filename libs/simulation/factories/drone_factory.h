#pragma once

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/drone_builder.h"
#include "libs/simulation/entities/drone.h"

namespace drone_simulation::simulation::factories {

class DroneFactory : public IFactory {
 public:
  virtual ~DroneFactory() {}

  anyBuilder createBuilder(const std::string& type) {
    if (type == "drone") {
      return new builders::DroneBuilder();
    }

    return {};
  }
};

}  // namespace drone_simulation::simulation::factories
