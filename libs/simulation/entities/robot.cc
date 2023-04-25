#include "robot.h"

#include <cmath>

#include "libs/geometry/vector3f.h"

namespace drone_simulation::simulation::entities {

void Robot::rotate(double angle) {
  geometry::Vector3f dirTmp = this->direction;
  this->direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  this->direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

void Robot::jump(double height) {}

void Robot::update(double dt, std::vector<IEntity*> scheduler) {}

}  // namespace drone_simulation::simulation::entities
