#ifndef BOARD_H
#define BOARD_H
#include "Buildings/TownHall.h"
#include "Buildings/Wall.h"
#include "Buildings/GoldMine.h"
#include "Buildings/ElixirCollector.h"
#include "Buildings/Barracks.h"
#include "./Position.h"
#include "Resources.h"
#include "Buildings/Building.h"
#include "Entities/Player.h"
#include "Entities/Npc.h"
#include "Entities/Troops/Troop.h"
#include <vector>
#include <memory>
#include <chrono>

class Board {
    int sizeX, sizeY;
    std::vector<std::shared_ptr<Building>> buildings;
    std::vector<std::shared_ptr<Npc>> npcs;
    std::vector<std::shared_ptr<Troop>> friendlyUnits;
    std::shared_ptr<Player> player;
    std::shared_ptr<TownHall> townHall;
    bool isGameOver = false;
    int enemyCounter = 0;
    int updatesSinceLastEnemy = 0;
    bool enemiesEnabled = false;
    std::chrono::time_point<std::chrono::steady_clock> gameStartTime;
public:
    Board(int w, int h);
    void setPlayer(std::shared_ptr<Player> p);
    std::shared_ptr<TownHall> getTownHall() const;
    const std::vector<std::shared_ptr<Building>>& getBuildings() const;
    const std::vector<std::shared_ptr<Npc>>& getNpcs() const;
    const std::vector<std::shared_ptr<Troop>>& getFriendlyUnits() const;
    void AddEnemy(std::shared_ptr<Npc> npc);
    void AddFriendlyUnit(std::shared_ptr<Troop> unit);
    bool IsGameOver() const;
    bool IsOutOfBounds(Position p) const;
    bool CollidesWithAny(const Building& b) const;
    bool AddBuilding(std::shared_ptr<Building> b);
    void SpawnEnemy();
    void UpdateAll();
    void Display() const;
};

#endif // BOARD_H
