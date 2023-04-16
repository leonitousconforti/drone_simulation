#pragma once

#include <iostream>
#include <vector>

namespace drone_simulation::geometry {

/// @brief A struct built solely to handle 3D point mathematics.
struct Point3f {
  float x;
  float y;
  float z;

  Point3f operator+(const Point3f& v);
  Point3f operator-(const Point3f& v);
  Point3f operator*(float m);
  Point3f operator/(float m);
  bool operator==(const Point3f& other);

  std::vector<float> toVec() const;
  float distanceBetween(const Point3f& other) const;

  friend std::ostream& operator<<(std::ostream& os, const Point3f& p);
};

}  // namespace drone_simulation::geometry
