#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "libs/simulation/simulation_model.h"
#include "load_models.h"
#include "populate_simulation.h"
#include "raylib.h"
#include "tools/cpp/runfiles/runfiles.h"

using namespace bazel::tools::cpp::runfiles;
using namespace drone_simulation::simulation;

int main(int argc, char* argv[]) {
  // Create a runfiles object to load models
  std::string rf_error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &rf_error));

  if (runfiles == nullptr) {
    std::cerr << rf_error << std::endl;
    return -1;
  }

  // Setup the window
  SetTraceLogLevel(LOG_WARNING);
  InitWindow(800, 500, "Drone Simulation");
  SetTargetFPS(60);
  DisableCursor();

  // Load the umn obj model (MUST happen after the window is created!)
  Model umn_model = loadUmnModel(runfiles.get());

  // Load all the glb models (MUST happen after the window is created!)
  auto all_models = loadAllGlbModels(runfiles.get());

  // Define the camera to look into our 3d world
  Camera camera;
  camera.fovy = 70.0f;
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.target = {0.0f, 0.0f, 0.0f};
  camera.position = {150.0f, 150.0f, 150.0f};
  camera.projection = CAMERA_PERSPECTIVE;

  // Populate the simulation with some starter entities
  populate_simulation();

  // Detects window close button or ESC key
  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode3D(camera);

    // UMN campus is approximately 260m above see level
    DrawModel(umn_model, {0, -260, 0}, 1.0f, WHITE);

    // Render every entity in the simulation that has a render model
    for (auto entity : SimulationModel::getInstance()->getEntities()) {
      if (!entity->hasTag("renderModel")) continue;

      const std::string renderModelName = entity->getTag("renderModel");
      const Vector3 position{entity->getPosition().x, entity->getPosition().y,
                             entity->getPosition().z};
      const float renderScale = entity->hasTag("renderScale")
                                    ? std::stof(entity->getTag("renderScale"))
                                    : 1.0f;

      const RenderModel rm = all_models[renderModelName];
      DrawModel(rm.model, position, renderScale, WHITE);
    }

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
  }

  // De-initialize
  for (auto m : all_models) UnloadModel(m.second.model);
  delete SimulationModel::getInstance();
  CloseWindow();
  return 0;
}
