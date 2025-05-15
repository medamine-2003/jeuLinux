#ifndef ENTITY_H
#define ENTITY_H

#include "Position.h"
#include <string>

class Entity {
protected:
    Position pos;
    std::string repr;
public:
    Entity(Position p, std::string emoji);
    virtual ~Entity() = default;
    Position getPosition() const;
    std::string getRepr() const;
    void Move(int dx, int dy, int maxX, int maxY);
};

#endif // ENTITY_H