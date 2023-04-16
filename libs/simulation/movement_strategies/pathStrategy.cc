#include "pathStrategy.h"

namespace drone_simulation::simulation::movement_strategies {

PathStrategy::PathStrategy(std::vector<geometry::Point3f> p)
    : path(p), index(0) {}

void PathStrategy::move(IEntity* entity, double dt) {
  if (isCompleted()) return;

  geometry::Vector3f vi = path[index];
  geometry::Vector3f dir = (vi - entity->getPosition()).unit();

  entity->setPosition(entity->getPosition() + dir * entity->getSpeed() * dt);
  entity->setDirection(dir);

  if (entity->getPosition().distanceBetween(vi) < 1) index++;
}

bool PathStrategy::isCompleted() { return index >= path.size(); }

}  // namespace drone_simulation::simulation::movement_strategies
