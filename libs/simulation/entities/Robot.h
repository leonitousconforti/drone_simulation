#pragma once

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
   * @brief Constructor
   */
  Robot();

  /**
   * @brief Destructor
   */
  ~Robot() override = default;

  /**
   * @brief Rotates the robot
   * @param angle The angle by which the robot should be rotated
   */
  void Rotate(double angle);
};

}  // namespace drone_simulation::simulation::entities
