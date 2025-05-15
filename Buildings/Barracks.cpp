#include "Barracks.h"
#include "Board.h"
#include "Entities/Troops/Barbarian.h"
#include "Entities/Troops/Archer.h"

Barracks::Barracks(Position p) 
    : Building(p, 3, 3, "🏕", Resources(50, 150), 2, true, 200),
      trainingCooldown(0), cooldownMax(10), isTraining(false), unitType(0) {}

bool Barracks::CanTrainUnit() const {
    return !isTraining;
}

void Barracks::StartTraining(int type) {
    if (!isTraining) {
        isTraining = true;
        unitType = type;
        trainingCooldown = cooldownMax;
    }
}

void Barracks::Update(Board& board) {
    if (isTraining) {
        if (--trainingCooldown <= 0) {
            isTraining = false;
            
            Position spawnPos = pos;
            const int dx[] = {0, 1, 0, -1, 1, 1, -1, -1};
            const int dy[] = {-1, 0, 1, 0, -1, 1, 1, -1};
            
            for (int i = 0; i < 8; ++i) {
                Position testPos(pos.x + dx[i], pos.y + dy[i]);
                if (!board.IsOutOfBounds(testPos)) {
                    spawnPos = testPos;
                    break;
                }
            }
            
            if (unitType == 0) {
                board.AddFriendlyUnit(std::make_shared<Barbarian>(spawnPos));
            } else {
                board.AddFriendlyUnit(std::make_shared<Archer>(spawnPos));
            }
        }
    }
}