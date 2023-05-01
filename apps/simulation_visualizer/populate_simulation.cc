#include "populate_simulation.h"

#include "libs/simulation/builders/drone_builder.h"
#include "libs/simulation/builders/robot_builder.h"
#include "libs/simulation/entities/robot.h"
#include "libs/simulation/simulation_model.h"

void populate_simulation() {
  using namespace drone_simulation::simulation;
  using namespace drone_simulation::simulation::builders;
  using namespace drone_simulation::simulation::entities;

  // SimulationModel* sm = SimulationModel::getInstance();

  // RobotBuilder* robotBuilder =
  //     std::get<RobotBuilder*>(sm->getEntityBuilder("robot"));

  // Robot* robot = robotBuilder->addPosition({0.0f, 0.0f, 0.0f})
  //                    ->addTag("renderModel", "robot")
  //                    ->construct();

  // sm->addEntity(robot);
}
