#pragma once

#include <variant>

#include "dragon_builder.h"
#include "drone_builder.h"
#include "helicopter_builder.h"
#include "human_builder.h"
#include "robot_builder.h"

namespace drone_simulation::simulation::builders {

using anyBuilder =
    std::variant<builders::DragonBuilder*, builders::DroneBuilder*,
                 builders::HelicopterBuilder*, builders::HumanBuilder*,
                 builders::RobotBuilder*>;

}
