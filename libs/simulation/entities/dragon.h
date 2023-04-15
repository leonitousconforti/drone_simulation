#pragma once

#include <vector>

#include "libs/simulation/IEntity.h"

namespace drone_simulation::simulation::entities {

/**
 * @class Dragon
 * @brief Represents a Dragon in a physical system. Dragons load
 * on startup of simulation and move to random locations.
 */
class Dragon : public IEntity {
 public:
  /**
   * @brief Dragons are created with a name
   * @param obj JSON object containing the Dragon's information
   */
  Dragon();

  /**
   * @brief Destructor
   */
  ~Dragon();

  /**
   * @brief Updates the Dragon's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  virtual void update(double dt, std::vector<IEntity*> scheduler);
};

}  // namespace drone_simulation::simulation::entities
