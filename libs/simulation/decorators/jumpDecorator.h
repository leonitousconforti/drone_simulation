#pragma once

#include "celebrationDecorator.h"

namespace drone_simulation::simulation::decorators {

/**
 * @brief this class inherits from the IStrategy class and is represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class JumpDecorator : public CelebrationDecorator {
 public:
  /**
   * @brief Construct a new Jump Decorator object
   *
   * @param strategy the strategy to decorate onto
   */
  JumpDecorator(IStrategy* strategy) : CelebrationDecorator(strategy){};

  /**
   * @brief JumpDecorator Destructor
   */
  ~JumpDecorator();

  /**
   * @brief Move the entity with the jump behavior for 4 seconds.
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void move(IEntity* entity, double dt);
};

}  // namespace drone_simulation::simulation::decorators
