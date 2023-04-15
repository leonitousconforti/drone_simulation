#pragma once

#include <iostream>
#include <vector>

namespace drone_simulation::geometry {

struct BoundingBox {
  std::vector<float> min;
  std::vector<float> max;
  std::vector<float> Normalize(std::vector<float> point) const;
  friend std::ostream& operator<<(std::ostream& os, const BoundingBox& bb);
};

}  // namespace drone_simulation::geometry
