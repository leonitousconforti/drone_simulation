#pragma once

#include "IEntity.h"
#include "libs/geometry/point3f.h"
#include "libs/geometry/vector3f.h"

namespace drone_simulation::simulation {

template <typename T = IEntity>
class IBuilder {
 public:
  virtual ~IBuilder<T>() {}
  IBuilder<T>() { this->entity = new T(); }

  T* construct() { return this->entity; }

  virtual IBuilder<T>* addPosition(geometry::Point3f position) {
    this->entity->setPosition(position);
    return this;
  }

  virtual IBuilder<T>* addDirection(geometry::Vector3f direction) {
    this->entity->setDirection(direction);
    return this;
  }

  virtual IBuilder<T>* addDestination(geometry::Point3f destination) {
    this->entity->setDestination(destination);
    return this;
  }

  virtual IBuilder<T>* addSpeed(float speed) {
    this->entity->setSpeed(speed);
    return this;
  }

  virtual IBuilder<T>* addAvailability(bool availability) {
    this->entity->setAvailability(availability);
    return this;
  }

  virtual IBuilder<T>* addTag(const std::string& key,
                              const std::string& value) {
    this->entity->addTag(key, value);
    return this;
  }

 protected:
  T* entity;
};

}  // namespace drone_simulation::simulation
