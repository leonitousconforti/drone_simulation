#pragma once

#include "IController.h"
#include "IEntity.h"
#include "libs/maps/graph.h"
#include "libs/simulation/entities/Drone.h"
#include "libs/simulation/entities/Robot.h"

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
  SimulationModel(IController& controller);

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * @brief Set the Graph for the SimulationModel
   * @param graph Type IGraph* contain the new graph for SimulationModel
   **/
  void setGraph(const IGraph* graph);

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   * which entity to create
   **/
  void createEntity(JsonObject& entity);

  /**
   * @brief Schedule a trip for an object in the scene
   * @param detail Type JsonObject contain the entity's reference to schedule
   * the detail of the trip being scheduled
   **/
  void scheduleTrip(JsonObject& details);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

 protected:
  IGraph* graph;
  IController& controller;
  std::vector<IEntity*> entities;
  CompositeFactory* compFactory;
};

}  // namespace drone_simulation::simulation
