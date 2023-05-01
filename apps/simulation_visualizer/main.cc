#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "libs/simulation/IEntity.h"
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
  SetTraceLogLevel(LOG_ALL);
  InitWindow(800, 450, "Drone Simulation");
  SetTargetFPS(60);
  DisableCursor();

  // Load the umn obj model
  Model umn_model = loadUmnModel(runfiles.get());

  // Load all the glb models (MUST happen after the window is create!)
  auto all_models = loadAllGlbModels(runfiles.get());

  // Define the camera to look into our 3d world
  Camera camera;
  camera.position = {5.0f, 5.0f, 25.0f};
  camera.target = {0.0f, 0.0f, 2.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  // Populate the simulation
  SimulationModel* sm = SimulationModel::getInstance();
  populate_simulation();

  // Detects window close button or ESC key
  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);

    DrawModel(umn_model, {0, 0, 0}, 0.2f, WHITE);
    for (IEntity* entity : sm->getEntities()) {
      const std::string renderModelName = entity->getTag("renderModel");
      const float renderScale = std::stof(entity->getTag("renderScale"));
      RenderModel rm = all_models[renderModelName];
      DrawModel(rm.model, {0, 0, 0}, renderScale, WHITE);
    }

    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
  }

  // De-initialize
  for (auto m : all_models) UnloadModel(m.second.model);
  CloseWindow();
  delete sm;
  return 0;
}
