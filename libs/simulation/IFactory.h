#pragma once

#include <optional>

#include "libs/simulation/builders/all.h"

namespace drone_simulation::simulation {

class IFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~IFactory() {}

  virtual std::optional<builders::anyBuilder> createBuilder(
      const std::string& type) = 0;
};

}  // namespace drone_simulation::simulation
