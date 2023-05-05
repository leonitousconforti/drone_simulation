#pragma once

#include <filesystem>
#include <iostream>
#include <string>
#include <unordered_map>

#include "raylib.h"
#include "tools/cpp/runfiles/runfiles.h"

using Runfiles = bazel::tools::cpp::runfiles::Runfiles;

/**
 * Represents any 3d model loaded from the filesystem. Just packs a Raylib model
 * and a Raylib ModelAnimations object into one so that it can be passed around
 * and returned from these functions easier
 */
typedef struct RenderModel {
  Model model;
  ModelAnimation* modelAnimations;
  unsigned int totalAnimations;
} RenderModel;

/**
 * Loads the umn campus model and its texture
 */
const Model loadUmnModel(Runfiles* runfiles) {
  const std::string umn_model_path = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/models/umn.obj");

  const std::string umn_texture_path = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/textures/"
      "umn_diffuse_4k.png");

  Model model = LoadModel(umn_model_path.c_str());
  Texture2D texture = LoadTexture(umn_texture_path.c_str());
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  return model;
}

/**
 * Loads all the glb models into a queryable map
 */
const std::unordered_map<std::string, RenderModel> loadAllGlbModels(
    Runfiles* runfiles) {
  std::unordered_map<std::string, RenderModel> models;

  // This is where the models directory is on the filesystem
  const std::string models_dir = runfiles->Rlocation(
      "drone_simulation/apps/simulation_visualizer/models/");

  // Iterate over all files in the models directory
  for (const auto& entry : std::filesystem::directory_iterator(models_dir)) {
    std::string name = entry.path().stem().string();
    const std::string extension = entry.path().extension().string();

    // Transform the name to lowercase
    transform(name.begin(), name.end(), name.begin(),
              [](unsigned char c) { return tolower(c); });

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
