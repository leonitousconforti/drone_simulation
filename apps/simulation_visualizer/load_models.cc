#include "load_models.h"

#include <filesystem>

const std::unordered_map<std::string, RenderModel> loadAllModels(
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
