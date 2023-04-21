#include "robot.h"

#include <math.h>

#include "libs/geometry/vector3f.h"

namespace drone_simulation::simulation::entities {

void Robot::Rotate(double angle) {
  geometry::Vector3f dirTmp = direction;
  this->direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  this->direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

}  // namespace drone_simulation::simulation::entities
