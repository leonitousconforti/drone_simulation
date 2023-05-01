#pragma once

#include <string>

#include "IBuilder.h"
#include "IEntity.h"
#include "IFactory.h"
#include "libs/geometry/point3f.h"
#include "libs/maps/graph.h"
#include "libs/simulation/builders/all.h"

namespace drone_simulation::simulation {

/**
 * @brief Class SimulationModel handling the transit simulation. it can
 * communicate with the controller
 **/
class SimulationModel {
 public:
  /**
   * @brief Singleton "constructor"
   */
  static SimulationModel* getInstance();

  /**
   * @brief Destructor
   */
  ~SimulationModel();

  /**
   * Singletons should not be cloneable.
   */
  SimulationModel(SimulationModel& other) = delete;

  /**
   * Singletons should not be assignable.
   */
  void operator=(const SimulationModel&) = delete;

  builders::anyBuilder getEntityBuilder(const std::string& entityType);

  /**
   * @brief Creates a new simulation entity
   * @param entity Type JsonObject contain the entity's reference to decide
   * which entity to create
   **/
  void addEntity(IEntity* entity);

  void addFactory(IFactory* factory);

  /**
   * @brief Schedule a trip for an entity
   **/
  void scheduleTrip(const std::string& tripName, geometry::Point3f start,
                    geometry::Point3f end);

  /**
   * @brief Update the simulation
   * @param dt Type double contain the time since update was last called.
   **/
  void update(double dt);

  const std::vector<IEntity*> getEntities() { return this->entities; }

 private:
  maps::IGraph* graph;
  std::vector<IEntity*> entities;
  std::vector<IFactory*> factories;
  static SimulationModel* instance;

  /**
   * @brief Default constructor that create the SimulationModel object
   **/
  SimulationModel();
};

}  // namespace drone_simulation::simulation
