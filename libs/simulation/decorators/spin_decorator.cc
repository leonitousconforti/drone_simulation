#include "spin_decorator.h"

namespace drone_simulation::simulation::decorators {

SpinDecorator::~SpinDecorator() { delete strategy; }

void SpinDecorator::move(IEntity* entity, double dt) {
  if (strategy->isCompleted() && !isCompleted()) {
    entity->rotate(dt * 10);
    time += dt;
  } else {
    strategy->move(entity, dt);
  }
}

}  // namespace drone_simulation::simulation::decorators
