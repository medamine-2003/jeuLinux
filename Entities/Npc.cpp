#include "Npc.h"

Npc::Npc(Position p, std::string emoji) : Entity(p, emoji), health(100) {}

void Npc::LoseHealth(int amount) { health -= amount; }

void Npc::MoveTowards(Position dest) {
    if (pos.x < dest.x) pos.x++;
    else if (pos.x > dest.x) pos.x--;
    if (pos.y < dest.y) pos.y++;
    else if (pos.y > dest.y) pos.y--;
}

int Npc::getHealth() const { return health; }