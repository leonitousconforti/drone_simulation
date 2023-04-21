#include "distance_function.h"

#include <cmath>

namespace drone_simulation::geometry {

float zeroDistance(const std::vector<float>& a, const std::vector<float>& b) {
  return 0;
}

float euclideanDistance(const std::vector<float>& a,
                        const std::vector<float>& b) {
  float sum = 0.0;
  for (size_t i = 0; i < a.size() && i < b.size(); i++) {
    float dist = (b[i] - a[i]);
    sum += dist * dist;
  }
  return std::sqrt(sum);
}

}  // namespace drone_simulation::geometry
