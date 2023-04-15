#include "vector3f.h"

#include <cmath>

namespace drone_simulation::geometry {

Vector3f::Vector3f(Point3f p) {
  this->x = p.x;
  this->y = p.y;
  this->z = p.z;
}

float Vector3f::Magnitude() { return std::sqrt(x * x + y * y + z * z); }

Vector3f Vector3f::Unit() {
  return Magnitude() == 0 ? (*this) : (*this) / Magnitude();
}

}  // namespace drone_simulation::geometry
