#pragma once

#include <optional>

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/all.h"

namespace drone_simulation::simulation::factories {

class DragonFactory : public IFactory {
 public:
  virtual ~DragonFactory() {}

  std::optional<builders::anyBuilder> createBuilder(const std::string& type) {
    if (type == "dragon") {
      return new builders::DragonBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
