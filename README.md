# Drone Simulation

[![Bazel Build](https://github.com/leonitousconforti/drone_simulation/actions/workflows/bazel_build.yml/badge.svg?branch=bazel)](https://github.com/leonitousconforti/drone_simulation/actions/workflows/bazel_build.yml)

__see the [README_Project.md](./README_Project.md) for the documentation about the project, here's what changed though__

## Switch from Make to Bazel

with bazel, we can have a real monorepo.

## This is the api I was going for

A little convoluted, but I feel it hits on most of the big design patterns we talked about in class

```c++
int main(int argc, char* argv[]) {
  // We use the singleton pattern to only allow one instance of the
  // SimulationModel at a time.
  SimulationModel* sm = SimulationModel::getInstance();

  // We use the factory pattern to get entity builders.
  DroneBuilder* droneBuilder =
      std::get<DroneBuilder*>(sm->getEntityBuilder("drone"));

  // We use the builder pattern to construct entities.
  Drone* drone = droneBuilder->addPosition()
                     ->addSpeed()
                     ->addDestination()
                     ->addAvailability()
                     ->construct();

  // We use the decorator pattern to add unique functionality to the drone.
  Drone* droneWithBat = new BatteryDecorator(drone);

  // Add the drone to the sim.
  sm->addEntity(droneWithBat);

  // And schedule a trip from the RecWel to Carlson school of Business which
  // uses the strategy pattern for movement.
  sm->scheduleTrip("My first trip!", {0, 0, 0}, {1, 1, 1});

  // ...
  delete sm;
  return 0;
}
```
