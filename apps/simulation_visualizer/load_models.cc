#include "load_models.h"

#include <filesystem>
#include <iostream>

const Model loadUmnModel(bazel::tools::cpp::runfiles::Runfiles* runfiles) {
  const std::string umn_model_path = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/models/umn.obj");

  const std::string umn_model_path2 = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/textures/umn_diffuse.png");

  Model model = LoadModel(umn_model_path.c_str());
  Texture2D texture = LoadTexture(umn_model_path2.c_str());
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  return model;
}

const std::unordered_map<std::string, RenderModel> loadAllGlbModels(
    bazel::tools::cpp::runfiles::Runfiles* runfiles) {
  std::unordered_map<std::string, RenderModel> models;

  // This is where the models directory is on the filesystem
  const std::string models_dir = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/models/");

  // Iterate over all files in the models directory
  for (const auto& entry : std::filesystem::directory_iterator(models_dir)) {
    std::string name = entry.path().stem().string();
    const std::string extension = entry.path().extension().string();

    // Transform the name to lowercase
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // Only load glb models
    if (extension != ".glb") {
      continue;
    }

    RenderModel rm;
    unsigned int c = 0;
    rm.model = LoadModel(entry.path().string().c_str());
    rm.modelAnimations = LoadModelAnimations(entry.path().string().c_str(), &c);
    rm.totalAnimations = c;
    models[name] = rm;
  }

  return models;
}
