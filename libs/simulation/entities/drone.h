#pragma once

#include <cmath>
#include <vector>

#include "libs/geometry/vector3f.h"
#include "libs/simulation/IEntity.h"

namespace drone_simulation::simulation::entities {

/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  virtual void update(double dt, std::vector<IEntity*> scheduler) {}

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  virtual void rotate(double angle) {
    geometry::Vector3f dirTmp = this->direction;
    direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
    direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
  }

  //  private:
  //   bool pickedUp;
};

}  // namespace drone_simulation::simulation::entities
