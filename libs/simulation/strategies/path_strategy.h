#pragma once

#include "libs/geometry/vector3f.h"
#include "libs/simulation/IEntity.h"
#include "libs/simulation/IStrategy.h"

namespace drone_simulation::simulation::movement_strategies {

/**
 * @brief this class inherits from the IStrategy class and is represents
 * a movement strategy where the entity simply moves along the given path
 */
class PathStrategy : public IStrategy {
 protected:
  std::vector<geometry::Point3f> path;
  unsigned int index;

 public:
  /**
   * @brief Construct a new PathStrategy Strategy object
   *
   * @param path the path to follow
   */
  PathStrategy(std::vector<geometry::Point3f> path = {})
      : path(path), index(0) {}

  /**
   * @brief Move toward next position in the path
   *
   * @param entity Entity to move
   * @param dt Delta Time
   */
  virtual void move(IEntity* entity, double dt) {
    if (isCompleted()) return;

    geometry::Vector3f vi = path[index];
    geometry::Vector3f dir = (vi - entity->getPosition()).unit();

    entity->setPosition(entity->getPosition() + dir * entity->getSpeed() * dt);
    entity->setDirection(dir);

    if (entity->getPosition().distanceBetween(vi) < 1) index++;
  }

  /**
   * @brief Check if the trip is completed by seeing if index
   *        has reached the end of the path
   *
   * @return True if complete, false if not complete
   */
  virtual bool isCompleted() { return index >= path.size(); }
};

}  // namespace drone_simulation::simulation::movement_strategies
