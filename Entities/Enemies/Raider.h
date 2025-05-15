#ifndef RAIDER_H
#define RAIDER_H

#include "Enemy.h"
#include <memory>
#include <vector>

class Board;
class Building;

class Raider : public Enemy {
    int updateCounter;
    const int updateDelay = 5;
public:
    Raider(Position p);
    std::shared_ptr<Building> GetNearestBuilding(const std::vector<std::shared_ptr<Building>>& buildings);
    void Update(Board& board) override;
};

#endif // RAIDER_H