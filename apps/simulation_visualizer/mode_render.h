#pragma once

#include "libs/simulation/IEntity.h"
#include "load_models.h"
#include "raylib.h"

using namespace drone_simulation;

void DrawEntity(simulation::IEntity* entity,
                std::unordered_map<std::string, RenderModel> models) {
  if (!entity->hasTag("renderModel")) {
    return;
  }

  const std::string renderModelName = entity->getTag("renderModel");
  const RenderModel rm = models[renderModelName];

  auto toRaylibVec = [](const geometry::Point3f& p) {
    return Vector3{p.x, p.y, p.z};
  };

  const float renderScale = entity->hasTag("renderScale")
                                ? std::stof(entity->getTag("renderScale"))
                                : 1.0f;

  DrawModel(rm.model, toRaylibVec(entity->getPosition()), renderScale, WHITE);
}

void resetView(Camera3D& camera) {
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.position = {0.0f, 150.0f, 100.0f};
  camera.projection = CAMERA_PERSPECTIVE;
}
