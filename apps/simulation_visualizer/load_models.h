#pragma once

#include <string>
#include <unordered_map>

#include "raylib.h"
#include "tools/cpp/runfiles/runfiles.h"

typedef struct RenderModel {
  Model model;
  ModelAnimation* modelAnimations;
  unsigned int totalAnimations;
} RenderModel;

const std::unordered_map<std::string, RenderModel> loadAllGlbModels(
    bazel::tools::cpp::runfiles::Runfiles* runfiles);

const Model loadUmnModel(bazel::tools::cpp::runfiles::Runfiles* runfiles);
