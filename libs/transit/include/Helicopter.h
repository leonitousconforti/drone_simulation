#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @class Helicopter
 * @brief Represents a helicopter in a physical system. Helicopters load 
 * on startup of smiulation and move to random locations.
 */
class Helicopter : public IEntity {
 public:
  /**
   * @brief Helicopters are created with a name
   * @param obj JSON object containing the Helicopter's information
   */
  Helicopter(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Helicopter();

  /**
   * @brief Gets the speed of the Helicopter
   * @return The speed of the Helicopter
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the Helicopter
   * @return The position of the Helicopter
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the Helicopter
   * @return The direction of the Helicopter
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the Helicopter
   * @return The destination of the Helicopter
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the Helicopter
   * @return The color of the Helicopter
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the Helicopter
   * @return The details information of the Helicopter
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Updates the helicopter's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the Helicopter
   * @param pos_ The new position of the Helicopter
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Helicopter
   * @param dir_ The new direction of the Helicopter
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Helicopter
   * @param des_ The new destination of the Helicopter
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the Helicopter
   * @param col_ The new color of the Helicopter
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that Helicopter cannot be copied.
   */
  Helicopter(const Helicopter& Helicopter) = delete;
  Helicopter& operator=(const Helicopter& Helicopter) = delete;

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
