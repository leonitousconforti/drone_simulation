#include <iostream>
#include <memory>
#include <string>

#include "libs/simulation/simulation_model.h"
#include "load_models.h"
#include "mode_instructions.h"
#include "mode_render.h"
#include "mode_scedule.h"
#include "populate_simulation.h"
#include "raylib.h"
#include "tools/cpp/runfiles/runfiles.h"

using Runfiles = bazel::tools::cpp::runfiles::Runfiles;
using SimulationModel = drone_simulation::simulation::SimulationModel;

enum class Mode { INSTRUCTIONS, RENDER, SCHEDULE_TRIP };

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

  // Set the initial application state
  Mode mode = Mode::INSTRUCTIONS;

  // Detects window close button or ESC key
  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    BeginDrawing();
    ClearBackground(SKYBLUE);
    BeginMode3D(camera);

    switch (mode) {
      // In the instructions mode, we display a graphic overlay with the
      // controls to the user.
      case Mode::INSTRUCTIONS:
        break;

      // In the render mode, we render update the simulation every frame and
      // then we render all the entities that have render data.
      case Mode::RENDER:
        DrawModel(umn_model, {0, -260, 0}, 1.0f, WHITE);
        for (auto entity : SimulationModel::getInstance()->getEntities())
          DrawEntity(entity, all_models);
        break;

      // In the schedule trip mode, we display a 2d map of the umn campus and
      // the user can select the start and end points for a trip as well as
      // provide a trip name
      case Mode::SCHEDULE_TRIP:
        break;
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
