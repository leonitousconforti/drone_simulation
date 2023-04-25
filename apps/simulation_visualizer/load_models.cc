#include "load_models.h"

#include <filesystem>

const std::unordered_map<std::string, SimulationModel> loadAllModels(
    bazel::tools::cpp::runfiles::Runfiles* runfiles) {
  std::unordered_map<std::string, SimulationModel> models;

  // This is where the models directory is on the filesystem
  const std::string models_dir = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/models/");

  // Iterate over all files in the models directory
  for (const auto& entry : std::filesystem::directory_iterator(models_dir)) {
    std::string name = entry.path().stem().string();
    const std::string extension = entry.path().extension();

    // Transform the name to lowercase
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    // Only load glb models
    if (extension != ".glb") {
      continue;
    }

    SimulationModel sm;
    unsigned int count = 0;
    sm.model = LoadModel(entry.path().c_str());
    sm.modelAnimations = LoadModelAnimations(entry.path().c_str(), &count);
    sm.totalAnimations = count;
    models[name] = sm;
  }

  return models;
}
