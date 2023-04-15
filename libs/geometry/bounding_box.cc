#include "bounding_box.h"

namespace drone_simulation::geometry {

std::vector<float> BoundingBox::Normalize(std::vector<float> point) const {
  std::vector<float> out;

  for (size_t i = 0; i < point.size(); i++) {
    float diff = max[i] - min[i];
    if (diff < 0.00001) {
      out.push_back(0.0);
    } else {
      out.push_back((point[i] - min[i]) / diff);
    }
  }

  return out;
}

std::ostream& operator<<(std::ostream& os, const BoundingBox& bb) {
  os << "[(";
  for (size_t i = 0; i < bb.min.size(); i++) {
    if (i > 0) {
      os << ", ";
    }
    os << bb.min[i];
  }
  os << "), (";
  for (size_t i = 0; i < bb.max.size(); i++) {
    if (i > 0) {
      os << ", ";
    }
    os << bb.max[i];
  }
  os << ")]";

  return os;
}

}  // namespace drone_simulation::geometry
