#pragma once

#include <vector>

#include "libs/simulation/IEntity.h"

namespace drone_simulation::simulation::entities {

/**
 * @class Human
 * @brief Represents a Human in a physical system. Humans load
 * on startup of simulation and move to random locations.
 */
class Human : public IEntity {
 public:
  /**
   * @brief Updates the Human's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void update(double dt, std::vector<IEntity*> scheduler);
};

}  // namespace drone_simulation::simulation::entities
