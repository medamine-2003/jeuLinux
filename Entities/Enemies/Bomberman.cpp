#include "Bomberman.h"
#include "../Board.h"
#include <climits>  // For INT_MAX
Bomberman::Bomberman(Position p) : Enemy(p, "💣", 10), updateCounter(0), hasExploded(false) {}

std::shared_ptr<Building> Bomberman::GetNearestWall(const std::vector<std::shared_ptr<Building>>& buildings) {
    std::shared_ptr<Building> nearest = nullptr;
    int minDist = INT_MAX;
    
    for (auto& b : buildings) {
        if (b->getRepr() == "🧱") {
            int d = pos.Distance(b->getPosition());
            if (d < minDist) {
                minDist = d;
                nearest = b;
            }
        }
    }
    
    if (!nearest) {
        for (auto& b : buildings) {
            int d = pos.Distance(b->getPosition());
            if (d < minDist) {
                minDist = d;
                nearest = b;
            }
        }
    }
    
    return nearest;
}

void Bomberman::Explode(Board& board) {
    const std::vector<std::shared_ptr<Building>>& buildings = board.getBuildings();
    for (auto& b : buildings) {
        if (pos.Distance(b->getPosition()) <= 2) {
            b->LoseHealth(100);
        }
    }
    
    hasExploded = true;
    health = 0;
}

void Bomberman::Update(Board& board) {
    if (++updateCounter < updateDelay) return;
    updateCounter = 0;
    
    if (hasExploded) return;
    
    for (auto& b : board.getBuildings()) {
        if (b->getRepr() == "🧱" && pos.Distance(b->getPosition()) <= 1) {
            Explode(board);
            return;
        }
    }
    
    auto target = GetNearestWall(board.getBuildings());
    if (!target) return;
    
    if (pos.Distance(target->getPosition()) <= 1) {
        Explode(board);
    } else {
        MoveTowards(target->getPosition());
    }
}
