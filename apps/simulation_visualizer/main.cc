#include <iostream>
#include <memory>
#include <string>

#include "raylib.h"
#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

int main(int argc, char* argv[]) {
  // Create a runfiles object to load models
  std::string error;
  std::unique_ptr<Runfiles> runfiles(Runfiles::Create(argv[0], &error));

  if (runfiles == nullptr) {
    std::cerr << error << std::endl;
    return -1;
  }

  // Find the robot model
  std::string robot_model_path = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/models/robot.glb");

  // Setup the window
  SetTraceLogLevel(LOG_WARNING);
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

  // Load robot model and set model position
  Model model = LoadModel(robot_model_path.c_str());
  Vector3 position = {0.0f, 0.0f, 0.0f};

  // Load robot model animations
  unsigned int animationIndex = 0;
  unsigned int animationsCount = 0;
  unsigned int animationCurrentFrame = 0;
  ModelAnimation* modelAnimations =
      LoadModelAnimations(robot_model_path.c_str(), &animationsCount);

  // Detects window close button or ESC key
  while (!WindowShouldClose()) {
    // Select current animation
    if (IsKeyPressed(KEY_UP))
      animationIndex = (animationIndex + 1) % animationsCount;
    else if (IsKeyPressed(KEY_DOWN))
      animationIndex = (animationIndex + animationsCount - 1) % animationsCount;

    // Update model animation
    ModelAnimation animation = modelAnimations[animationIndex];
    animationCurrentFrame = (animationCurrentFrame + 1) % animation.frameCount;
    UpdateModelAnimation(model, animation, animationCurrentFrame);

    // Draw the scene
    UpdateCamera(&camera, CAMERA_THIRD_PERSON);
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camera);
    DrawModel(model, position, 1.0f, WHITE);
    DrawGrid(10, 1.0f);
    EndMode3D();
    DrawText("Use UP/DOWN arrow keys to switch animation", 10, 10, 20, GRAY);
    EndDrawing();
  }

  // De-initialize
  UnloadModel(model);
  CloseWindow();
  return 0;
}
