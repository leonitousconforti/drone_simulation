#pragma once

#include <functional>
#include <vector>

namespace drone_simulation::geometry {

typedef std::function<const float(const std::vector<float>&,
                                  const std::vector<float>&)>
    DistanceFunction;

float zeroDistance(const std::vector<float>& a, const std::vector<float>& b);
float euclideanDistance(const std::vector<float>& a,
                        const std::vector<float>& b);

}  // namespace drone_simulation::geometry
