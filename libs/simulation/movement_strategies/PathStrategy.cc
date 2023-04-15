#include "PathStrategy.h"

namespace drone_simulation::simulation::movement_strategies {

PathStrategy::PathStrategy(std::vector<geometry::Point3f> p)
    : path(p), index(0) {}

void PathStrategy::Move(IEntity* entity, double dt) {
  if (IsCompleted()) return;

  geometry::Vector3f vi = path[index];
  geometry::Vector3f dir = (vi - entity->getPosition()).unit();

  entity->setPosition(entity->getPosition() + dir * entity->getSpeed() * dt);
  entity->setDirection(dir);

  if (entity->getPosition().Distance(vi) < 1) index++;
}

bool PathStrategy::IsCompleted() { return index >= path.size(); }

}  // namespace drone_simulation::simulation::movement_strategies
