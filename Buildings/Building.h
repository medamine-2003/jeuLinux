#ifndef BUILDING_H
#define BUILDING_H

#include "Position.h"
#include "Resources.h"
#include <string>

class Board;

class Building {
protected:
    Position pos;
    int sizeX, sizeY, maxInstances, health;
    std::string repr;
    Resources cost;
    bool hasCorners;
public:
    Building(Position p, int sx, int sy, std::string emoji, Resources cost, int maxInst, bool corners = true, int hp = 100);
    virtual ~Building() = default;
    virtual void Update(Board&);
    virtual Resources Collect();
    Position getPosition() const;
    std::string getRepr() const;
    Resources getCost() const;
    int getMaxInstances() const;
    int getHealth() const;
    int getSizeX() const;
    int getSizeY() const;
    bool getHasCorners() const;
    void LoseHealth(int dmg);
    bool isInside(Position p) const;
    bool isOnBorder(Position p) const;
    bool isCorner(Position p) const;
    bool isHorizontalBorder(Position p) const;
    bool isVerticalBorder(Position p) const;
    bool isCenter(Position p) const;
    bool CollidesWith(const Building& other) const;
};

#endif // BUILDING_H