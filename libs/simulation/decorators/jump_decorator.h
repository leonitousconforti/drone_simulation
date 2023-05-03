#pragma once

#include "celebration_decorator.h"

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
  ~JumpDecorator() { delete strategy; }

  /**
   * @brief Move the entity with the jump behavior for 4 seconds.
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void move(IEntity* entity, double dt) {
    if (strategy->isCompleted() && !isCompleted()) {
      entity->jump(dt * 10);
      time += dt;
    } else {
      strategy->move(entity, dt);
    }
  }
};

}  // namespace drone_simulation::simulation::decorators
