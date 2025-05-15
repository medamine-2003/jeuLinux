#include "Archer.h"
#include "../../Board.h"
#include <climits>

Archer::Archer(Position p) : Troop(p, "🏹", 3), updateCounter(0) {}

std::shared_ptr<Npc> Archer::GetNearestEnemyInRange(const std::vector<std::shared_ptr<Npc>>& npcs) {
    std::shared_ptr<Npc> nearest = nullptr;
    int minDist = INT_MAX;
    
    for (auto& npc : npcs) {
        if (npc->getRepr() != "🏹" && npc->getRepr() != "⚔️") {
            int d = pos.Distance(npc->getPosition());
            if (d <= attackRange && d < minDist) {
                minDist = d;
                nearest = npc;
            }
        }
    }
    
    return nearest;
}

void Archer::Update(Board& board) {
    if (++updateCounter < updateDelay) return;
    updateCounter = 0;
    
    auto enemies = board.getNpcs();
    auto target = GetNearestEnemyInRange(enemies);
    
    if (!target) return;
    
    int distance = pos.Distance(target->getPosition());
    
    if (distance <= attackRange) {
        AttackEnemy(target);
    } else {
        MoveTowards(target->getPosition());
    }
}
