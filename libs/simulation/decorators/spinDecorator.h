#pragma once

#include "celebrationDecorator.h"

namespace drone_simulation::simulation::decorators {

/**
 * @brief this class inherits from the IStrategy class and is represents
 * a celebration decorator where the entity will celebrate according to it.
 */
class SpinDecorator : public CelebrationDecorator {
 public:
  /**
   * @brief Construct a new Spin Decorator object
   *
   * @param strategy the strategy to decorate onto
   */
  SpinDecorator(IStrategy* strategy) : CelebrationDecorator(strategy){};

  /**
   * @brief SpinDecorator Destructor
   */
  ~SpinDecorator();

  /**
   * @brief Move the entity with the spin behavior for 4 seconds.
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void move(IEntity* entity, double dt);
};

}  // namespace drone_simulation::simulation::decorators
