#include "load_models.h"

#include <filesystem>
#include <iostream>

const std::unordered_map<std::string, SimulationModel> loadAllModels(
    bazel::tools::cpp::runfiles::Runfiles* runfiles) {
  std::unordered_map<std::string, SimulationModel> models;

  const std::string models_dir = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/models/");

  for (const auto& entry : std::filesystem::directory_iterator(models_dir)) {
    std::string extension = entry.path().extension();
    std::string filename = entry.path().stem().string();

    if (extension != ".glb") {
      continue;
    }

    std::transform(filename.begin(), filename.end(), filename.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    SimulationModel sm;
    unsigned int count = 0;
    sm.model = LoadModel(entry.path().c_str());
    sm.modelAnimations = LoadModelAnimations(entry.path().c_str(), &count);
    sm.totalAnimations = count;
    models[filename] = sm;
  }

  return models;
}
