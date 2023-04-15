#include "jumpDecorator.h"

namespace drone_simulation::simulation::decorators {

JumpDecorator::~JumpDecorator() { delete strategy; }

void JumpDecorator::move(IEntity* entity, double dt) {
  if (strategy->isCompleted() && !isCompleted()) {
    entity->jump(dt * 10);
    time += dt;
  } else {
    strategy->move(entity, dt);
  }
}

}  // namespace drone_simulation::simulation::decorators
