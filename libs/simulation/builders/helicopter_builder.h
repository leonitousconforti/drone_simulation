#pragma once

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/entities/helicopter.h"

namespace drone_simulation::simulation::builders {

class HelicopterBuilder : public IBuilder<entities::Helicopter> {
  HelicopterBuilder* addBlades(int number) { return this; }

  virtual HelicopterBuilder* addDetails(const std::any data) {
    IBuilder::addDetails(data);
    return this;
  }
};

}  // namespace drone_simulation::simulation::builders
