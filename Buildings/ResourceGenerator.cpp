#include "ResourceGenerator.h"
#include "Board.h"

ResourceGenerator::ResourceGenerator(Position p, int sx, int sy, 
                     std::string emptyEmoji, std::string fullEmoji,
                     Resources cost, int maxInst, 
                     Resources prodRate, int hp)
    : Building(p, sx, sy, emptyEmoji, cost, maxInst, true, hp),
      currentAmount(0), fullRepr(fullEmoji), productionRate(prodRate) {}

bool ResourceGenerator::IsFull() const { return currentAmount >= capacity; }
int ResourceGenerator::GetCurrentAmount() const { return currentAmount; }

void ResourceGenerator::Update(Board& board) {
    if (!IsFull()) {
        currentAmount = std::min(capacity, currentAmount + 
                          productionRate.getGold() + 
                          productionRate.getElixir());
        if (IsFull()) {
            repr = fullRepr;
        }
    }
}

Resources ResourceGenerator::Collect() {
    Resources collected((currentAmount * productionRate.getGold()) / capacity,
                      (currentAmount * productionRate.getElixir()) / capacity);
    currentAmount = 0;
    repr = productionRate.getGold() > 0 ? "💰" : "🧪";
    return collected;
}