#pragma once

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/human_builder.h"
#include "libs/simulation/entities/human.h"

namespace drone_simulation::simulation::factories {

class HumanFactory : public IFactory {
 public:
  virtual ~HumanFactory() {}

  std::optional<anyBuilder> createBuilder(const std::string& type) {
    if (type == "human") {
      return new builders::HumanBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
