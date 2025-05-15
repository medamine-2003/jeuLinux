#include "Player.h"
#include "Board.h"

Player::Player(Position p) : Entity(p, "🏃"), res(400, 400) {}

Resources& Player::getResources() { return res; }
bool Player::CanAfford(const Resources& cost) const { return res.CanAfford(cost); }
void Player::Spend(const Resources& cost) { res.Spend(cost); }
void Player::AddResources(const Resources& amount) { res.Add(amount); }

void Player::Interact(Board& board) {
    Position p = getPosition();
    for (auto& b : board.getBuildings()) {
        if (b->isInside(p)) {
            if (auto generator = dynamic_cast<ResourceGenerator*>(b.get())) {
                AddResources(generator->Collect());
                break;
            }
        }
    }
}