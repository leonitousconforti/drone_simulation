#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"
#include "tools/cpp/runfiles/runfiles.h"

typedef struct SimulationModel {
  Model model;
  ModelAnimation* modelAnimations;
  unsigned int totalAnimations;
} SimulationModel;

const std::unordered_map<std::string, SimulationModel> loadAllModels(
    bazel::tools::cpp::runfiles::Runfiles* runfiles);
