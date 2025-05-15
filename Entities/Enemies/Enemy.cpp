#include "Enemy.h"
#include "../../Buildings/Building.h"

Enemy::Enemy(Position p, std::string emoji, int dmg) 
    : Npc(p, emoji), attackDamage(dmg) {}

void Enemy::AttackBuilding(std::shared_ptr<Building> b) {
    if (b) b->LoseHealth(attackDamage);
}
