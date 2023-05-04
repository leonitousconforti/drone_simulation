#pragma once

#include <any>
#include <map>

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

  virtual IBuilder<T>* addPosition(geometry::Point3f position) final {
    this->entity->setPosition(position);
    return this;
  }

  virtual IBuilder<T>* addDirection(geometry::Vector3f direction) final {
    this->entity->setDirection(direction);
    return this;
  }

  virtual IBuilder<T>* addDestination(geometry::Point3f destination) final {
    this->entity->setDestination(destination);
    return this;
  }

  virtual IBuilder<T>* addSpeed(float speed) final {
    this->entity->setSpeed(speed);
    return this;
  }

  virtual IBuilder<T>* addAvailability(bool availability) final {
    this->entity->setAvailability(availability);
    return this;
  }

  virtual IBuilder<T>* addTag(const std::string& key,
                              const std::string& value) final {
    this->entity->addTag(key, value);
    return this;
  }

  virtual IBuilder<T>* addDetails(const std::map<std::string, std::any> data) {
    using namespace std;
    using namespace geometry;

    if (data.count("speed")) {
      this->addSpeed(any_cast<float>(data.at("speed")));
    }

    if (data.count("position")) {
      this->addPosition(any_cast<Point3f>(data.at("position")));
    }

    if (data.count("direction")) {
      this->addDirection(any_cast<Vector3f>(data.at("direction")));
    }

    if (data.count("destination")) {
      this->addDestination(any_cast<Point3f>(data.at("destination")));
    }

    if (data.count("availability")) {
      this->addAvailability(any_cast<bool>(data.at("availability")));
    }

    if (data.count("renderModel")) {
      this->addTag("renderModel", any_cast<string>(data.at("renderModel")));
    }

    if (data.count("renderScale")) {
      this->addTag("renderScale", any_cast<string>(data.at("renderScale")));
    }

    return this;
  }

 protected:
  T* entity;
};

}  // namespace drone_simulation::simulation
