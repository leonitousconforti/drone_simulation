#pragma once

#include <iostream>

#include "point3f.h"

namespace drone_simulation::geometry {

struct BoundingBox {
  Point3f min;
  Point3f max;
  Point3f normalize(Point3f point) const;

  friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bb);
};

}  // namespace drone_simulation::geometry
