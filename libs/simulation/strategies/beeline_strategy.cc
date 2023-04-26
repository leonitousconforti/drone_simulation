#include "beeline_strategy.h"

namespace drone_simulation::simulation::movement_strategies {

BeelineStrategy::BeelineStrategy(geometry::Vector3f start,
                                 geometry::Vector3f end) {}

void BeelineStrategy::move(IEntity* entity, double dt) {}
bool BeelineStrategy::isCompleted() { return true; }

}  // namespace drone_simulation::simulation::movement_strategies
