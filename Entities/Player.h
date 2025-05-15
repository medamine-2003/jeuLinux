#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "../Resources.h"

class Board;

class Player : public Entity {
    Resources res;
public:
    Player(Position p);
    Resources& getResources();
    bool CanAfford(const Resources& cost) const;
    void Spend(const Resources& cost);
    void AddResources(const Resources& amount);
    void Interact(Board& board);
};

#endif // PLAYER_H
