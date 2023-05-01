#pragma once

#include <optional>

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/IEntity.h"
#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/human_builder.h"

namespace drone_simulation::simulation::factories {

class HumanFactory : public IFactory {
 public:
  virtual ~HumanFactory() {}

  std::optional<IBuilder<IEntity>*> createBuilder(const std::string& type) {
    if (type == "human") {
      return (IBuilder<IEntity>*)new builders::HumanBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
