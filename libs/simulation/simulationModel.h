#pragma once

#include <string>

#include "IEntity.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/simulation/entities/drone.h"
#include "libs/simulation/entities/robot.h"

namespace drone_simulation::simulation {

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel {
 public:
  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel();

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type IGraph* contain the new graph for SimulationModel
   **/
  void setGraph(const maps::IGraph* graph);

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   * which entity to create
   **/
  void addEntity(IEntity* entity);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   * the detail of the trip being scheduled
   **/
  void scheduleTrip(const std::string& name, geometry::Point3f start,
                    geometry::Point3f end);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

 protected:
  maps::IGraph* graph;
  std::vector<IEntity*> entities;
};

}  // namespace drone_simulation::simulation
