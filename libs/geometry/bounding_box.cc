#include "bounding_box.h"

namespace drone_simulation::geometry {

Point3f BoundingBox::normalize(Point3f point) const {
  auto normalize_1d = [](float val, float min, float max) {
    float diff = max - min;
    if (diff < 0.00001)
      return 0.0f;
    else
      return (val - min) / diff;
  };

  return {normalize_1d(point.x, min.x, max.x),
          normalize_1d(point.y, min.y, max.y),
          normalize_1d(point.z, min.z, max.z)};
}

std::ostream& operator<<(std::ostream& os, const BoundingBox& bb) {
  os << "[" << bb.min << ", " << bb.max << "]";
  return os;
}

}  // namespace drone_simulation::geometry
