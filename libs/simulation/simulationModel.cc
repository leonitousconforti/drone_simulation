#include "simulationModel.h"

namespace drone_simulation::simulation {

SimulationModel::SimulationModel() {}

SimulationModel::~SimulationModel() {
  for (size_t i = 0; i < entities.size(); i++) {
    delete entities[i];
  }
  delete graph;
}

void SimulationModel::addEntity(IEntity* entity) {
  entity->setGraph(this->graph);
  entities.push_back(entity);
}

/// Schedules a trip for an object in the scene
void SimulationModel::scheduleTrip(const std::string& name,
                                   geometry::Point3f start,
                                   geometry::Point3f end) {
  for (auto entity : entities) {
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      entity->SetStrategyName(strategyName);
      scheduler.push_back(entity);
      break;
    }
  }
}

/// Updates the simulation
void SimulationModel::update(double dt) {
  for (size_t i = 0; i < this->entities.size(); i++) {
    entities[i]->update(dt);
  }
}

}  // namespace drone_simulation::simulation
