#pragma once

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
  void update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void rotate(double angle);

  //  private:
  //   bool pickedUp;
};

}  // namespace drone_simulation::simulation::entities
