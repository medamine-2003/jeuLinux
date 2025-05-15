#ifndef TROOP_H
#define TROOP_H

#include "../Npc.h"
#include <memory>
#include <vector>

class Board;
class Npc;

class Troop : public Npc {
protected:
    int attackDamage;
public:
    Troop(Position p, std::string emoji, int dmg = 1);
    void AttackEnemy(std::shared_ptr<Npc> enemy);
    virtual void Update(Board& board) = 0;
};

#endif // TROOP_H