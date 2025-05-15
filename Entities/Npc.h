#ifndef NPC_H
#define NPC_H

#include "Entity.h"
#include <string>

class Board;

class Npc : public Entity {
protected:
    int health;
public:
    Npc(Position p, std::string emoji);
    void LoseHealth(int amount);
    void MoveTowards(Position dest);
    virtual void Update(Board&) = 0;
    int getHealth() const;
};

#endif // NPC_H
