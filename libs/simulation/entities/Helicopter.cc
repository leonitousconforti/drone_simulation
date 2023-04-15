#define _USE_MATH_DEFINES
#include "Helicopter.h"

#include <cmath>
#include <limits>
#include <random>

#include "BeelineStrategy.h"

Helicopter::Helicopter(JsonObject& obj) : details(obj) {
  JsonArray pos = obj["position"];
  position = {pos[0], pos[1], pos[2]};
  JsonArray dir = obj["direction"];
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  toFinalDestination = nullptr;
}

Helicopter::~Helicopter() {
  // Delete dynamically allocated variables
  delete graph;
  delete toFinalDestination;
}

void Helicopter::Update(double dt, std::vector<IEntity*> scheduler) {
  if (toFinalDestination) {
    toFinalDestination->Move(this, dt);

    if (toFinalDestination->IsCompleted()) {
      delete toFinalDestination;

      toFinalDestination = nullptr;
    }
  } else {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> x(-1400, 1500);
    std::uniform_real_distribution<> z(-800, 800);

    Vector3 finalDestination(x(gen), 500, z(gen));
    toFinalDestination =
        new BeelineStrategy(this->GetPosition(), finalDestination);
  }
}
