#ifndef RESOURCEGENERATOR_H
#define RESOURCEGENERATOR_H

#include "Building.h"

class ResourceGenerator : public Building {
protected:
    int currentAmount;
    const int capacity = 100;
    std::string fullRepr;
    Resources productionRate;
public:
    ResourceGenerator(Position p, int sx, int sy, 
                     std::string emptyEmoji, std::string fullEmoji,
                     Resources cost, int maxInst, 
                     Resources prodRate, int hp = 100);
    bool IsFull() const;
    int GetCurrentAmount() const;
    void Update(Board& board) override;
    Resources Collect() override;
};

#endif // RESOURCEGENERATOR_H