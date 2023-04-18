#include "celebration_decorator.h"

namespace drone_simulation::simulation::decorators {

CelebrationDecorator::CelebrationDecorator(IStrategy* strategy) {
  this->strategy = strategy;
  time = 0;
}

CelebrationDecorator::~CelebrationDecorator() { delete strategy; }

bool CelebrationDecorator::isCompleted() {
  if (time >= 4.0) {
    return true;
  } else {
    return false;
  }
}

}  // namespace drone_simulation::simulation::decorators
