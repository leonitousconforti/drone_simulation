#include "bounding_box.h"

namespace drone_simulation::geometry {

Point3f BoundingBox::Normalize(Point3f point) const {
  auto normalize = [](float val, float min, float max) {
    float diff = max - min;
    if (diff < 0.00001)
      return 0.0f;
    else
      return (val - min) / diff;
  };

  return {normalize(point.x, min.x, max.x), normalize(point.y, min.y, max.y),
          normalize(point.z, min.z, max.z)};
}

std::ostream& operator<<(std::ostream& os, const BoundingBox& bb) {
  os << "[" << bb.min << ", " << bb.max << "]";
  return os;
}

}  // namespace drone_simulation::geometry
