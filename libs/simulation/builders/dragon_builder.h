#pragma once

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/entities/dragon.h"

namespace drone_simulation::simulation::builders {

class DragonBuilder : public IBuilder<entities::Dragon> {
  DragonBuilder* addFireBreath() {
    this->addTag("fireBreath", "true");
    return this;
  }

  virtual DragonBuilder* addDetails(const std::any data) {
    IBuilder::addDetails(data);
    return this;
  }
};

}  // namespace drone_simulation::simulation::builders
