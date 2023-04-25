#pragma once

#include <vector>

#include "libs/simulation/IEntity.h"

namespace drone_simulation::simulation::entities {

/**
 * @class Robot
 * @brief Represents a robot in a physical system
 *
 * Robots move using euler integration based on a specified
 * velocity and direction.
 */
class Robot : public IEntity {
 public:
  /**
   * @brief Rotates the robot
   * @param angle The angle by which the robot should be rotated
   */
  void rotate(double angle);

  /**
   * @brief Makes the robot jump
   * @param height The height at which the robot should jump
   */
  void jump(double height);

  void update(double dt, std::vector<IEntity*> scheduler);
};

}  // namespace drone_simulation::simulation::entities
