#pragma once

#include <optional>

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/IEntity.h"
#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/drone_builder.h"

namespace drone_simulation::simulation::factories {

class DroneFactory : public IFactory {
 public:
  virtual ~DroneFactory() {}

  std::optional<IBuilder<IEntity>*> createBuilder(const std::string& type) {
    if (type == "drone") {
      return (IBuilder<IEntity>*)new builders::DroneBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
