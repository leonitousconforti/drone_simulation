#include "simulation_model.h"

#include "libs/simulation/factories/dragon_factory.h"
#include "libs/simulation/factories/drone_factory.h"
#include "libs/simulation/factories/helicopter_factory.h"
#include "libs/simulation/factories/human_factory.h"
#include "libs/simulation/factories/robot_factory.h"

namespace drone_simulation::simulation {

SimulationModel::SimulationModel() {
  this->addFactory(new factories::DroneFactory());
  this->addFactory(new factories::HumanFactory());
  this->addFactory(new factories::RobotFactory());
  this->addFactory(new factories::DragonFactory());
  this->addFactory(new factories::HelicopterFactory());
}

SimulationModel::~SimulationModel() {
  for (size_t i = 0; i < this->entities.size(); i++) delete this->entities[i];
  for (size_t i = 0; i < this->factories.size(); i++) delete this->factories[i];
  delete graph;
}

SimulationModel* SimulationModel::instance = nullptr;

SimulationModel* SimulationModel::getInstance() {
  if (instance == nullptr) {
    instance = new SimulationModel();
  }
  return instance;
}

anyBuilder getEntityBuilder(const std::string& forEntity) { return {}; }

void SimulationModel::addEntity(IEntity* entity) {
  this->entities.push_back(entity);
}

void SimulationModel::addFactory(IFactory* factory) {
  this->factories.push_back(factory);
}

void SimulationModel::scheduleTrip(const std::string& name,
                                   geometry::Point3f start,
                                   geometry::Point3f end) {}

void SimulationModel::update(double dt) {
  for (size_t i = 0; i < this->entities.size(); i++) {
    entities[i]->update(dt, this->entities);
    std::cout << this->entities[i]->getSpeed() << std::endl;
  }
}

}  // namespace drone_simulation::simulation
