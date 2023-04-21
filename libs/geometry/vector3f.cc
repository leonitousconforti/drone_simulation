#include "vector3f.h"

#include <cmath>

namespace drone_simulation::geometry {

Vector3f::Vector3f(Point3f p) {
  this->x = p.x;
  this->y = p.y;
  this->z = p.z;
}

Vector3f::Vector3f(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

float Vector3f::magnitude() { return std::sqrt(x * x + y * y + z * z); }

Vector3f Vector3f::unit() {
  return magnitude() == 0 ? (*this) : (*this) / magnitude();
}

Vector3f Vector3f::operator+(const Vector3f& v) {
  return {this->x + v.x, this->y + v.y, this->z + v.z};
}

Vector3f Vector3f::operator-(const Vector3f& v) {
  return {this->x - v.x, this->y - v.y, this->z - v.z};
}

Vector3f Vector3f::operator*(float m) {
  return {m * this->x, m * this->y, m * this->z};
}

Vector3f Vector3f::operator/(float m) {
  return {this->x / m, this->y / m, this->z / m};
}

bool Vector3f::operator==(const Vector3f& other) {
  return this->x == other.x && this->y == other.y && this->z == other.z;
}

}  // namespace drone_simulation::geometry
