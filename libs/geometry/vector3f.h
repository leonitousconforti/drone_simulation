#pragma once

#include "point3f.h"

namespace drone_simulation::geometry {

/// @brief A struct built solely to handle 3D vector mathematics.
struct Vector3f : public Point3f {
  Vector3f(Point3f p);
  Vector3f(float x, float y, float z);

  float magnitude();
  Vector3f unit();

  Vector3f operator+(const Vector3f& v);
  Vector3f operator-(const Vector3f& v);
  Vector3f operator*(float m);
  Vector3f operator/(float m);
  bool operator==(const Vector3f& other);
};

}  // namespace drone_simulation::geometry
