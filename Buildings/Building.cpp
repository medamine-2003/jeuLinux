#include "Building.h"

Building::Building(Position p, int sx, int sy, std::string emoji, Resources cost, int maxInst, bool corners, int hp)
    : pos(p), sizeX(sx), sizeY(sy), repr(emoji), cost(cost), maxInstances(maxInst), hasCorners(corners), health(hp) {}

void Building::Update(Board&) {}
Resources Building::Collect() { return Resources(0, 0); }

Position Building::getPosition() const { return pos; }
std::string Building::getRepr() const { return repr; }
Resources Building::getCost() const { return cost; }
int Building::getMaxInstances() const { return maxInstances; }
int Building::getHealth() const { return health; }
int Building::getSizeX() const { return sizeX; }
int Building::getSizeY() const { return sizeY; }
bool Building::getHasCorners() const { return hasCorners; }
void Building::LoseHealth(int dmg) { health -= dmg; }

bool Building::isInside(Position p) const {
    int xMin = pos.x - sizeX/2, xMax = pos.x + sizeX/2;
    int yMin = pos.y - sizeY/2, yMax = pos.y + sizeY/2;
    return p.x >= xMin && p.x <= xMax && p.y >= yMin && p.y <= yMax;
}

bool Building::isOnBorder(Position p) const {
    int xMin = pos.x - sizeX/2, xMax = pos.x + sizeX/2;
    int yMin = pos.y - sizeY/2, yMax = pos.y + sizeY/2;
    return (p.x == xMin || p.x == xMax || p.y == yMin || p.y == yMax) && 
           (p.x >= xMin && p.x <= xMax && p.y >= yMin && p.y <= yMax);
}

bool Building::isCorner(Position p) const {
    int xMin = pos.x - sizeX/2, xMax = pos.x + sizeX/2;
    int yMin = pos.y - sizeY/2, yMax = pos.y + sizeY/2;
    return ((p.x == xMin || p.x == xMax) && (p.y == yMin || p.y == yMax));
}

bool Building::isHorizontalBorder(Position p) const {
    int yMin = pos.y - sizeY/2, yMax = pos.y + sizeY/2;
    return (p.y == yMin || p.y == yMax) && isOnBorder(p);
}

bool Building::isVerticalBorder(Position p) const {
    int xMin = pos.x - sizeX/2, xMax = pos.x + sizeX/2;
    return (p.x == xMin || p.x == xMax) && isOnBorder(p);
}

bool Building::isCenter(Position p) const {
    return p.x == pos.x && p.y == pos.y;
}

bool Building::CollidesWith(const Building& other) const {
    for (int dx = -1; dx <= 1; ++dx)
        for (int dy = -1; dy <= 1; ++dy)
            if (isInside({other.pos.x + dx, other.pos.y + dy}))
                return true;
    return false;
}