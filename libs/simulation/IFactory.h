#pragma once

#include <variant>

#include "libs/simulation/builders/dragon_builder.h"
#include "libs/simulation/builders/drone_builder.h"
#include "libs/simulation/builders/helicopter_builder.h"
#include "libs/simulation/builders/human_builder.h"
#include "libs/simulation/builders/robot_builder.h"

namespace drone_simulation::simulation {

using anyBuilder =
    std::variant<builders::DragonBuilder*, builders::DroneBuilder*,
                 builders::HelicopterBuilder*, builders::HumanBuilder*,
                 builders::RobotBuilder*>;

class IFactory {
 public:
  /**
   * @brief Destructor for IEntityFactory class.
   **/
  virtual ~IFactory() {}

  virtual anyBuilder createBuilder(const std::string& type) = 0;
};

}  // namespace drone_simulation::simulation
