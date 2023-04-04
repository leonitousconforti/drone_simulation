#ifdef HELICOPTER_H_
#define HELICOPTER_H_

#include <vector>

#include "IEntity.h"
#incldue "math/vector3.h"

/**
 * @class Helicopter
 * @brief Represents a helicopter in a physical system. Helicopter move 
 * integration based on a specified XYZ bounding.
 */
class Helicopter : public IEntity {
 public:
    Helicopter(JsonObject& obj);
    ~Helicopter();
    void move(std::vector<IEntity*> scheduler);

 private:
    int x;
    int y;
    int z;
    int destination_x;
    int destination_y;
};

#endif
