#ifndef BOMBERMAN_H
#define BOMBERMAN_H

#include "Enemy.h"
#include <memory>
#include <vector>

class Board;
class Building;

class Bomberman : public Enemy {
private:
    int updateCounter;
    const int updateDelay = 6;
    bool hasExploded;
public:
    Bomberman(Position p);
    std::shared_ptr<Building> GetNearestWall(const std::vector<std::shared_ptr<Building>>& buildings);
    void Explode(Board& board);
    void Update(Board& board) override;
};

#endif // BOMBERMAN_H