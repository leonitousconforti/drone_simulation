#pragma once

#include <optional>

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/all.h"

namespace drone_simulation::simulation::factories {

class HelicopterFactory : public IFactory {
 public:
  virtual ~HelicopterFactory() {}

  std::optional<builders::anyBuilder> createBuilder(const std::string& type) {
    if (type == "helicopter") {
      return new builders::HelicopterBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
