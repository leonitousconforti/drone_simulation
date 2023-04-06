#ifndef DRAGON_H_
#define DRAGON_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @class Dragon
 * @brief Represents a Dragon in a physical system. Dragons load 
 * on startup of smiulation and move to random locations.
 */
class Dragon : public IEntity {
 public:
  /**
   * @brief Dragons are created with a name
   * @param obj JSON object containing the Dragon's information
   */
  Dragon(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Dragon();

  /**
   * @brief Gets the speed of the Dragon
   * @return The speed of the Dragon
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the position of the Dragon
   * @return The position of the Dragon
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the direction of the Dragon
   * @return The direction of the Dragon
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the destination of the Dragon
   * @return The destination of the Dragon
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the color of the Dragon
   * @return The color of the Dragon
   */
  std::string GetColor() const { return color; }

  /**
   * @brief Gets the details information of the Dragon
   * @return The details information of the Dragon
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Updates the Dragon's position
   * @param dt Delta time
   * @param scheduler Vector containing all the entities in the system
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the Dragon
   * @param pos_ The new position of the Dragon
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Dragon
   * @param dir_ The new direction of the Dragon
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Dragon
   * @param des_ The new destination of the Dragon
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the color of the Dragon
   * @param col_ The new color of the Dragon
   */
  void SetColor(std::string col_) { color = col_; }

  /**
   * @brief Removing the copy constructor and assignment operator
   * so that Dragon cannot be copied.
   */
  Dragon(const Dragon& Dragon) = delete;
  Dragon& operator=(const Dragon& Dragon) = delete;

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
