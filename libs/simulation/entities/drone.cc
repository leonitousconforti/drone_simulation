#include "drone.h"

#include <cmath>

namespace drone_simulation::simulation::entities {

void Drone::GetNearestEntity(std::vector<IEntity*> scheduler) {}

void Drone::Update(double dt, std::vector<IEntity*> scheduler) {}

void Drone::Rotate(double angle) {
  geometry::Vector3f dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Drone::Jump(double height) {}

}  // namespace drone_simulation::simulation::entities
