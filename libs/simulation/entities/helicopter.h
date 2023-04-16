#pragma once

#include <vector>

#include "libs/simulation/IEntity.h"

namespace drone_simulation::simulation::entities {

/**
 * @class Helicopter
 * @brief Represents a helicopter in a physical system. Helicopters load
 * on startup of simulation and move to random locations.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Updates the helicopter's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

 private:
  float speed;
};

}  // namespace drone_simulation::simulation::entities
