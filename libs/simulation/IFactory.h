#pragma once

#include <optional>

#include "libs/simulation/IBuilder.h"
#include "libs/simulation/IEntity.h"

namespace drone_simulation::simulation {

class IFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~IFactory() {}

  virtual std::optional<IBuilder<IEntity>*> createBuilder(
      const std::string& type) = 0;
};

}  // namespace drone_simulation::simulation
