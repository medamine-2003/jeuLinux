#include "Barbarian.h"
#include "../../Board.h"
#include <climits>

Barbarian::Barbarian(Position p) : Troop(p, "⚔️", 5), updateCounter(0) {}

std::shared_ptr<Npc> Barbarian::GetNearestEnemy(const std::vector<std::shared_ptr<Npc>>& npcs) {
    std::shared_ptr<Npc> nearest = nullptr;
    int minDist = INT_MAX;
    
    for (auto& npc : npcs) {
        if (npc->getRepr() != "⚔️" && npc->getRepr() != "🏹") {
            int d = pos.Distance(npc->getPosition());
            if (d < minDist) {
                minDist = d;
                nearest = npc;
            }
        }
    }
    
    return nearest;
}

void Barbarian::Update(Board& board) {
    if (++updateCounter < updateDelay) return;
    updateCounter = 0;
    
    auto enemies = board.getNpcs();
    auto target = GetNearestEnemy(enemies);
    
    if (!target) return;
    
    int distance = pos.Distance(target->getPosition());
    
    if (distance <= 1) {
        AttackEnemy(target);
    } else {
        MoveTowards(target->getPosition());
    }
}
