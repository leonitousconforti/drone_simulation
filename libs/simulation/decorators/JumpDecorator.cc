#include "JumpDecorator.h"

namespace drone_simulation::simulation::decorators {

JumpDecorator::~JumpDecorator() {
  // Delete dynamically allocated variables
  delete strategy;
}

void JumpDecorator::Move(IEntity* entity, double dt) {
  if (strategy->IsCompleted() && !IsCompleted()) {
    entity->Jump(dt * 10);
    time += dt;
  } else {
    strategy->Move(entity, dt);
  }
}

}  // namespace drone_simulation::simulation::decorators
