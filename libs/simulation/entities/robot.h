#pragma once

#include <cmath>
#include <vector>

#include "libs/geometry/vector3f.h"
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
  virtual void rotate(double angle) {
    geometry::Vector3f dirTmp = this->direction;
    this->direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
    this->direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
  }

  /**
   * @brief Makes the robot jump
   * @param height The height at which the robot should jump
   */
  virtual void jump(double height) {}

  virtual void update(double dt, std::vector<IEntity*> scheduler) {}
};

}  // namespace drone_simulation::simulation::entities
