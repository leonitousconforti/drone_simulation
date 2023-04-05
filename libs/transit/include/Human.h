#ifndef HUMAN_H_
#define HUMAN_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @class Human
 * @brief Represents a Human in a physical system. Humans load 
 * on startup of smiulation and move to random locations.
 */
class Human : public IEntity {
 public:
  /**
   * @brief Humans are created with a name
   * @param obj JSON object containing the Human's information
   */
  Human(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Human();

  /**
   * @brief Gets the speed of the Human
   * @return The speed of the Human
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the Human
   * @return The position of the Human
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the Human
   * @return The direction of the Human
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the Human
   * @return The destination of the Human
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the Human
   * @return The color of the Human
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the Human
   * @return The details information of the Human
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Updates the Human's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the Human
   * @param pos_ The new position of the Human
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Human
   * @param dir_ The new direction of the Human
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Human
   * @param des_ The new destination of the Human
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the Human
   * @param col_ The new color of the Human
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that Human cannot be copied.
   */
  Human(const Human& Human) = delete;
  Human& operator=(const Human& Human) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  std::string color = "None";  // None means default color
  Vector3 destination;
  float speed;
  IStrategy* toFinalDestination = nullptr;
};

#endif
