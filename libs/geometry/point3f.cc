#include "point3f.h"

#include <cmath>

namespace drone_simulation::geometry {

Point3f Point3f::operator+(const Point3f& v) {
  return Point3f{this->x + v.x, this->y + v.y, this->z + v.z};
}

Point3f Point3f::operator-(const Point3f& v) {
  return Point3f{this->x - v.x, this->y - v.y, this->z - v.z};
}

Point3f Point3f::operator*(float m) {
  return Point3f{m * this->x, m * this->y, m * this->z};
}

Point3f Point3f::operator/(float m) {
  return Point3f{this->x / m, this->y / m, this->z / m};
}

bool Point3f::operator==(const Point3f& other) {
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

float Point3f::distanceBetween(const Point3f& other) const {
  return euclideanDistance(this->toVec(), other.toVec());
}

std::vector<float> Point3f::toVec() const {
  return std::vector<float>{x, y, z};
}

}  // namespace drone_simulation::geometry
