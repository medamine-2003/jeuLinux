#include "Entity.h"

Entity::Entity(Position p, std::string emoji) : pos(p), repr(emoji) {}

Position Entity::getPosition() const { return pos; }
std::string Entity::getRepr() const { return repr; }

void Entity::Move(int dx, int dy, int maxX, int maxY) {
    int nx = pos.x + dx, ny = pos.y + dy;
    if (nx >= 0 && nx < maxX && ny >= 0 && ny < maxY)
        pos = {nx, ny};
}