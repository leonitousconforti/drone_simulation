#pragma once

#include "IEntity.h"

namespace drone_simulation::simulation {

/**
 * @brief Strategy interface
 *
 */
class IStrategy {
 public:
  virtual ~IStrategy() {}

  /**
   * @brief Move toward next position
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void move(IEntity* entity, double dt) = 0;

  /**
   * @brief Check if the trip is completed
   *
   * @return True if complete, false if not complete
   */
  virtual bool isCompleted() = 0;
};

}  // namespace drone_simulation::simulation
