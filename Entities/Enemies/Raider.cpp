#include "Raider.h"
#include "../../Board.h"
#include <climits>  // Add this line for INT_MAX

// Rest of your code...
Raider::Raider(Position p) : Enemy(p, "🗡", 2), updateCounter(0) {}

std::shared_ptr<Building> Raider::GetNearestBuilding(const std::vector<std::shared_ptr<Building>>& buildings) {
    std::shared_ptr<Building> nearest = nullptr;
    int minDist = INT_MAX;
    for (auto& b : buildings) {
        int d = pos.Distance(b->getPosition());
        if (d < minDist) {
            minDist = d;
            nearest = b;
        }
    }
    return nearest;
}

void Raider::Update(Board& board) {
    if (++updateCounter < updateDelay) return;
    updateCounter = 0;

    for (auto& b : board.getBuildings()) {
        if (b->getRepr() == "🧱" && b->isInside(getPosition())) {
            b->LoseHealth(200);
            health = 0;
            return;
        }
    }

    auto townHall = board.getTownHall();
    if (townHall && getPosition().Distance(townHall->getPosition()) < 10) {
        if (getPosition() == townHall->getPosition()) {
            AttackBuilding(townHall);
        } else {
            MoveTowards(townHall->getPosition());
        }
        return;
    }

    auto target = GetNearestBuilding(board.getBuildings());
    if (!target) return;

    if (getPosition() == target->getPosition()) {
        AttackBuilding(target);
    } else {
        MoveTowards(target->getPosition());
    }
}
