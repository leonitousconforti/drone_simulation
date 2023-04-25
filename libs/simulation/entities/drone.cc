#include "drone.h"

#include <cmath>

namespace drone_simulation::simulation::entities {

void Drone::update(double dt, std::vector<IEntity*> scheduler) {}

void Drone::rotate(double angle) {
  geometry::Vector3f dirTmp = this->direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

}  // namespace drone_simulation::simulation::entities
