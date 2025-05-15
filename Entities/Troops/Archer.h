#ifndef ARCHER_H
#define ARCHER_H

#include "Troop.h"
#include <memory>
#include <vector>

class Board;
class Npc;

class Archer : public Troop {
private:
    int updateCounter;
    const int updateDelay = 4;
    const int attackRange = 5;
public:
    Archer(Position p);
    std::shared_ptr<Npc> GetNearestEnemyInRange(const std::vector<std::shared_ptr<Npc>>& npcs);
    void Update(Board& board) override;
};

#endif // ARCHER_H