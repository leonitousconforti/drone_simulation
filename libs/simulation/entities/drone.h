#pragma once

#include <vector>

#include "libs/geometry/vector3f.h"
#include "libs/simulation/IEntity.h"

namespace drone_simulation::simulation::entities {

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
/**
 * @class Drone
 * @brief Represents a drone in a physical system. Drones move using euler
 * integration based on a specified velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Gets the nearest entity in the scheduler
   * @param scheduler Vector containing all the entities in the system
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
   * @brief Updates the drone's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Rotates the drone
   * @param angle The angle by which the drone should be rotated
   */
  void Rotate(double angle);

  /**
   * @brief Makes the drone jump
   * @param height The height at which the drone should jump
   */
  void Jump(double height);

  //  private:
  //   float jumpHeight = 0;
  //   bool goUp = true;
  //   bool pickedUp;
};

}  // namespace drone_simulation::simulation::entities
