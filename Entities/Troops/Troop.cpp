#include "Troop.h"

Troop::Troop(Position p, std::string emoji, int dmg) 
    : Npc(p, emoji), attackDamage(dmg) {}

void Troop::AttackEnemy(std::shared_ptr<Npc> enemy) {
    if (enemy) enemy->LoseHealth(attackDamage);
}