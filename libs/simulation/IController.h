#pragma once

#include "IEntity.h"

namespace drone_simulation::simulation {

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View
/// Controller Pattern
/**
 * @brief class for IController used for transit service. Uses the Model View
 **/
class IController {
 public:
  /**
   * @brief A destructor for IController
   **/
  virtual ~IController() {}

  /**
   * @brief Add the entity to the program
   * @param entity Type IEntity contain entity object
   **/
  virtual void addEntity(const IEntity& entity) = 0;

  /**
   * @brief To update the entity information and add it to the program
   * @param entity Type IEntity contain entity object
   **/
  virtual void updateEntity(const IEntity& entity) = 0;

  /**
   * @brief To remove the entity from the program
   * @param id Type int contain the ID of the entity object
   **/
  virtual void removeEntity(int id) = 0;
};

}  // namespace drone_simulation::simulation
