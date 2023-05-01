#pragma once

#include <optional>

#include "libs/simulation/IFactory.h"
#include "libs/simulation/builders/all.h"

namespace drone_simulation::simulation::factories {

class HumanFactory : public IFactory {
 public:
  virtual ~HumanFactory() {}

  std::optional<builders::anyBuilder> createBuilder(const std::string& type) {
    if (type == "human") {
      return new builders::HumanBuilder();
    }

    return std::nullopt;
  }
};

}  // namespace drone_simulation::simulation::factories
