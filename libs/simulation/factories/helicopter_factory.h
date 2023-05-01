#pragma once

#include <optional>

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/IEntity.h"
#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/helicopter_builder.h"

namespace drone_simulation::simulation::factories {

class HelicopterFactory : public IFactory {
 public:
  virtual ~HelicopterFactory() {}

  std::optional<IBuilder<IEntity>*> createBuilder(const std::string& type) {
    if (type == "helicopter") {
      return (IBuilder<IEntity>*)new builders::HelicopterBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
