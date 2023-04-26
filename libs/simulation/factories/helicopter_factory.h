#pragma once

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/helicopter_builder.h"
#include "libs/simulation/entities/helicopter.h"

namespace drone_simulation::simulation::factories {

class HelicopterFactory : public IFactory {
 public:
  virtual ~HelicopterFactory() {}

  std::optional<anyBuilder> createBuilder(const std::string& type) {
    if (type == "helicopter") {
      return new builders::HelicopterBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
