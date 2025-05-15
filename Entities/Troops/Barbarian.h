#ifndef BARBARIAN_H
#define BARBARIAN_H

#include "Troop.h"
#include <memory>
#include <vector>

class Board;
class Npc;

class Barbarian : public Troop {
private:
    int updateCounter;
    const int updateDelay = 3;
public:
    Barbarian(Position p);
    std::shared_ptr<Npc> GetNearestEnemy(const std::vector<std::shared_ptr<Npc>>& npcs);
    void Update(Board& board) override;
};

#endif // BARBARIAN_H