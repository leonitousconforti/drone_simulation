#pragma once

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/helicopter_builder.h"
#include "libs/simulation/entities/helicopter.h"

namespace drone_simulation::simulation::factories {

class HelicopterFactory : public IFactory {
 public:
  virtual ~HelicopterFactory() {}

  anyBuilder createBuilder(const std::string& type) {
    if (type == "helicopter") {
      return new builders::HelicopterBuilder();
    }

    return {};
  }
};

}  // namespace drone_simulation::simulation::factories
