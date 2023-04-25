#pragma once

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/dragon_builder.h"
#include "libs/simulation/entities/dragon.h"

namespace drone_simulation::simulation::factories {

class DragonFactory : public IFactory {
 public:
  virtual ~DragonFactory() {}

  anyBuilder createBuilder(const std::string& type) {
    if (type == "dragon") {
      return new builders::DragonBuilder();
    }

    return {};
  }
};

}  // namespace drone_simulation::simulation::factories
