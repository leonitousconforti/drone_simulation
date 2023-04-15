#pragma once

#include <vector>

#include "libs/geometry/color.h"
#include "libs/geometry/point3f.h"
#include "libs/geometry/vector3f.h"
#include "libs/maps/graph.h"
#include "libs/simulation/IStrategy.h"

namespace drone_simulation::simulation {

/**
 * @class IEntity
 * @brief Represents an entity in a physical system.
 *
 * An IEntity object has a unique ID, a position, a direction, a destination,
 * and details. It also has a speed, which determines how fast the entity moves
 * in the physical system. Subclasses of IEntity can override the `Update`
 * function to implement their own movement behavior.
 */
class IEntity {
 public:
  /**
   * @brief Constructor that assigns a unique ID to the entity.
   */
  IEntity(float speed, geometry::Color color) {
    static int currentId = 0;
    id = currentId;
    currentId++;

    this->speed = speed;
    this->color = color;
  }

  /**
   * @brief Virtual destructor for IEntity.
   */
  virtual ~IEntity() { delete graph; }

  /**
   * @brief Gets the ID of the entity.
   * @return The ID of the entity.
   */
  virtual int getId() const final { return id; }

  /**
   * @brief Gets the position of the entity.
   * @return The position of the entity.
   */
  virtual geometry::Point3f getPosition() const final { return this->position; }

  /**
   * @brief Gets the direction of the entity.
   * @return The direction of the entity.
   */
  virtual geometry::Vector3f getDirection() const final {
    return this->direction;
  }

  /**
   * @brief Gets the destination of the entity.
   * @return The destination of the entity.
   */
  virtual geometry::Point3f getDestination() const final {
    return this->destination;
  }

  /**
   * @brief Gets the color of the drone
   * @return The color of the drone
   */
  virtual geometry::Color getColor() const final { return this->color; }

  /**
   * @brief Gets the speed of the entity.
   * @return The speed of the entity.
   */
  virtual float getSpeed() const final { return this->speed; }

  /**
   * @brief Gets the availability of the entity.
   * @return The availability of the entity.
   */
  virtual bool getAvailability() const final { return this->available; }

  /**
   * @brief Sets the availability of the entity.
   * @param choice The desired availability of the entity.
   */
  virtual void setAvailability(bool available) final {
    this->available = available;
  }

  /**
   * @brief Sets the graph object used by the entity in the simulation.
   * @param graph The IGraph object to be used.
   */
  virtual void setGraph(maps::IGraph* graph) final { this->graph = graph; }

  /**
   * @brief Sets the position of the entity.
   * @param pos_ The desired position of the entity.
   */
  virtual void setPosition(geometry::Point3f position) final {
    this->position = position;
  }

  /**
   *@brief Set the direction of the entity.
   *@param dir_ The new direction of the entity.
   */
  virtual void setDirection(geometry::Vector3f direction) final {
    this->direction = direction;
  }

  /**
   *@brief Set the destination of the entity.
   *@param des_ The new destination of the entity.
   */
  virtual void setDestination(geometry::Point3f destination) final {
    this->destination = destination;
  }

  /**
   * @brief Sets the color of the drone
   * @param col_ The new color of the drone
   */
  virtual void setColor(geometry::Color color) final { this->color = color; }

  /**
   * @brief Sets the speed of the drone
   * @param speed The new speed of the drone
   */
  virtual void setSpeed(float speed) final { this->speed = speed; }

  /**
   * @brief Updates the entity's position in the physical system.
   * @param dt The time step of the update.
   * @param scheduler The list of all entities in the system.
   */
  virtual void update(double dt, std::vector<IEntity*> scheduler) = 0;

  /**
   * @brief Rotate the entity.
   * @param angle The angle to rotate the entity by.
   */
  virtual void rotate(double angle) {}

  /**
   * @brief Make the entity jump.
   * @param height The height to make the entity jump.
   */
  virtual void jump(double height) {}

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that Dragon cannot be copied.
   */
  IEntity(const IEntity& entity) = delete;
  IEntity& operator=(const IEntity& entity) = delete;

 protected:
  int id;
  float speed;
  bool available;

  maps::IGraph* graph;
  geometry::Color color;
  geometry::Point3f position;
  geometry::Vector3f direction;
  geometry::Point3f destination;
};

}  // namespace drone_simulation::simulation
