#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "libs/simulation/IEntity.h"
#include "libs/simulation/entities/robot.h"
#include "load_models.h"
#include "raylib.h"
#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

int main(int argc, char* argv[]) {
  // Create a runfiles object to load models
  std::string rf_error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &rf_error));

  if (runfiles == nullptr) {
    std::cerr << rf_error << std::endl;
    return -1;
  }

  // Hush all logging to just warnings and error
  SetTraceLogLevel(LOG_WARNING);

  // Load all the models
  auto all_models = loadAllModels(runfiles.get());
  std::cout << all_models.at("robot").totalAnimations << std::endl;

  // Setup the window
  InitWindow(800, 450, "Drone Simulation");
  SetTargetFPS(60);
  DisableCursor();

  // Define the camera to look into our 3d world
  Camera camera;
  camera.position = {5.0f, 5.0f, 5.0f};
  camera.target = {0.0f, 2.0f, 0.0f};
  camera.up = {0.0f, 1.0f, 0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;

  // Detects window close button or ESC key
  while (!WindowShouldClose()) {
    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    DrawGrid(10, 1.0f);
    EndMode3D();
    EndDrawing();
  }

  // De-initialize
  CloseWindow();
  for (auto m : all_models) {
    UnloadModel(m.second.model);
  }
  return 0;
}
