/**
 * Example program to setup a simulation
 */

#include "libs/simulation/builders/drone_builder.h"
#include "libs/simulation/decorators/battery_decorator.h"
#include "libs/simulation/decorators/jump_decorator.h"
#include "libs/simulation/entities/drone.h"
#include "libs/simulation/simulation_model.h"
#include "libs/simulation/strategies/astar_strategy.h"

using namespace drone_simulation::simulation;
using namespace drone_simulation::simulation::builders;
using namespace drone_simulation::simulation::entities;
using namespace drone_simulation::simulation::decorators;
using namespace drone_simulation::simulation::movement_strategies;

int main(int argc, char* argv[]) {
  // We use the singleton pattern to only allow one instance of the
  // SimulationModel at a time.
  SimulationModel* sm = SimulationModel::getInstance();

  // We use the factory pattern to get entity builders.
  DroneBuilder* droneBuilder =
      std::get<DroneBuilder*>(sm->getEntityBuilder("drone"));

  // We use the builder pattern to construct entities.
  Drone* drone = droneBuilder->addPosition({})
                     ->addSpeed(1.0f)
                     ->addDestination({})
                     ->addAvailability(true)
                     ->construct();

  // We use the decorator pattern to add unique functionality to the drone
  Drone* droneWithBat = new BatteryDecorator(drone);

  // Add the drone to the sim
  sm->addEntity(droneWithBat);

  // And schedule a trip from the RecWel to Carlson school of Business
  sm->scheduleTrip("My first trip!", {0, 0, 0}, {1, 1, 1});

  // ...
  sm->update(1.0f);

  // Don't forget to cleanup (since we didn't use a smart pointer)
  delete sm;
  return 0;
}
