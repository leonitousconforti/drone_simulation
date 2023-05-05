#include "populate_simulation.h"

#include "libs/geometry/point3f.h"
#include "libs/simulation/builders/drone_builder.h"
#include "libs/simulation/builders/robot_builder.h"
#include "libs/simulation/entities/robot.h"
#include "libs/simulation/simulation_model.h"

using namespace drone_simulation::geometry;
using namespace drone_simulation::simulation;
using namespace drone_simulation::simulation::builders;
using namespace drone_simulation::simulation::entities;

/**
 * Here is how you can create a new builder for a specific entity type. These
 * builders allow you to specify exactly how an entity should look, without
 * needing to specify any of the "fluff" that you might not need. and then use
 * the builder to construct an entity of that type
 */
void populate_simulation_v1() {
  SimulationModel* sm = SimulationModel::getInstance();
  auto robotBuilder = new RobotBuilder();

  Robot* robot = robotBuilder->addPosition({0.0f, 0.0f, 0.0f})
                     ->addTag("renderModel", "robot")
                     ->addTag("renderScale", "2.5")
                     ->construct();

  sm->addEntity(robot);
  delete robotBuilder;
}

/**
 * Another example, showing how to apply a decorator using the builder
 */
void populate_simulation_v2() {
  SimulationModel* sm = SimulationModel::getInstance();
  auto droneBuilder = new DroneBuilder();

  Drone* drone = droneBuilder->addPosition({0.0f, 10.0f, 0.0f})
                     ->addTag("renderModel", "drone")
                     ->addTag("renderScale", "4.5")
                     ->construct();

  sm->addEntity(drone);
  delete droneBuilder;
}

/**
 * How to create an entity using the builder returned by a factory
 */
void populate_simulation_v3() {
  SimulationModel* sm = SimulationModel::getInstance();
  auto humanBuilder = sm->getEntityBuilder("human");

  IEntity* human = humanBuilder->addPosition({0.0f, 20.0f, 0.0f})
                       ->addTag("renderModel", "human")
                       ->construct();

  sm->addEntity(human);
  delete humanBuilder;
}

/**
 * How to create an entity using the builder returned by a factory and details
 */
void populate_simulation_v4() {
  SimulationModel* sm = SimulationModel::getInstance();

  const std::map<std::string, std::any> dragonDetails = {
      {"speed", 1.0f},
      {"position", Point3f{0.0f, 30.0f, 0.0f}},
      {"renderModel", std::string("dragon")}};

  auto dragonBuilder = sm->getEntityBuilder("dragon");
  IEntity* dragon = dragonBuilder->addDetails(dragonDetails)->construct();

  sm->addEntity(dragon);
  delete dragonBuilder;
}

/**
 * How to create an entity using the builder returned by a factory and set its
 * animation state
 */
void populate_simulation_v5() {
  SimulationModel* sm = SimulationModel::getInstance();
  auto helicopterBuilder = sm->getEntityBuilder("helicopter");

  IEntity* helicopter = helicopterBuilder->addDetails({})
                            ->addTag("renderAnimation", "1")
                            ->construct();

  sm->addEntity(helicopter);
  delete helicopterBuilder;
}

/**
 * This module aims to showcase the various ways one can add an entity to the
 * simulation
 */
void populate_simulation() {
  populate_simulation_v1();
  populate_simulation_v2();
  populate_simulation_v3();
  populate_simulation_v4();
  populate_simulation_v5();
}
