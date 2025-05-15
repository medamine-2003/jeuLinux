#ifndef BARRACK_H
#define BARRACK_H

#include "Building.h"

class Barracks : public Building {
private:
    int trainingCooldown;
    int cooldownMax;
    bool isTraining;
    int unitType;
public:
    Barracks(Position p);
    bool CanTrainUnit() const;
    void StartTraining(int type);
    void Update(Board& board) override;
};

#endif // BARRACK_H