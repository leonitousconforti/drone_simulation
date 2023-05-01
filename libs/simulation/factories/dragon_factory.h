#pragma once

#include <optional>

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/IEntity.h"
#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/dragon_builder.h"

namespace drone_simulation::simulation::factories {

class DragonFactory : public IFactory {
 public:
  virtual ~DragonFactory() {}

  std::optional<IBuilder<IEntity>*> createBuilder(const std::string& type) {
    if (type == "dragon") {
      return (IBuilder<IEntity>*)new builders::DragonBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
