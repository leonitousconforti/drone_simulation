#pragma once

#include "IEntity.h"

namespace drone_simulation::simulation {

template <typename T = IEntity>
class IBuilder {
 public:
  virtual ~IBuilder<T>() {}
  IBuilder<T>() { this->entity = new T(); }

  T* construct() { return this->entity; }

  virtual IBuilder<T>* addSpeed() { return this; }
  virtual IBuilder<T>* addPosition() { return this; }
  virtual IBuilder<T>* addDirection() { return this; }
  virtual IBuilder<T>* addDestination() { return this; }
  virtual IBuilder<T>* addAvailability() { return this; }

 protected:
  T* entity;
};

}  // namespace drone_simulation::simulation
