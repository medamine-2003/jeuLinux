#ifndef ENEMY_H
#define ENEMY_H

#include "../Npc.h"
#include <memory>

class Building;
class Board;

class Enemy : public Npc {
protected:
    int attackDamage;
public:
    Enemy(Position p, std::string emoji, int dmg = 1);
    void AttackBuilding(std::shared_ptr<Building> b);
};

#endif // ENEMY_H