#include "Board.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Entities/Enemies/Bomberman.h"
#include "Entities/Enemies/Raider.h"

Board::Board(int w, int h) : sizeX(w), sizeY(h) {
    townHall = std::make_shared<TownHall>(Position(w/2, h/2));
    buildings.push_back(townHall);
    gameStartTime = std::chrono::steady_clock::now();
    std::srand(std::time(nullptr));
}

void Board::setPlayer(std::shared_ptr<Player> p) { player = p; }
std::shared_ptr<TownHall> Board::getTownHall() const { return townHall; }
const std::vector<std::shared_ptr<Building>>& Board::getBuildings() const { return buildings; }
const std::vector<std::shared_ptr<Npc>>& Board::getNpcs() const { return npcs; }
const std::vector<std::shared_ptr<Troop>>& Board::getFriendlyUnits() const { return friendlyUnits; }

void Board::AddEnemy(std::shared_ptr<Npc> npc) { 
    npcs.push_back(npc);
    enemyCounter++;
}

void Board::AddFriendlyUnit(std::shared_ptr<Troop> unit) {
    friendlyUnits.push_back(unit);
}

bool Board::IsGameOver() const { return isGameOver || (townHall && townHall->getHealth() <= 0); }

bool Board::IsOutOfBounds(Position p) const {
    return p.x < 0 || p.y < 0 || p.x >= sizeX || p.y >= sizeY;
}

bool Board::CollidesWithAny(const Building& b) const {
    if (b.getRepr() == "🧱") {
        for (auto& existing : buildings) {
            if (existing->getRepr() != "🧱" && existing->CollidesWith(b)) {
                return true;
            }
            else if (existing->getRepr() == "🧱" && existing->getPosition() == b.getPosition()) {
                return true;
            }
        }
        return false;
    }
    
    for (auto& existing : buildings)
        if (existing->CollidesWith(b)) return true;
    return false;
}

bool Board::AddBuilding(std::shared_ptr<Building> b) {
    if (IsOutOfBounds(b->getPosition()) || CollidesWithAny(*b)) return false;
    
    int count = std::count_if(buildings.begin(), buildings.end(), 
        [&](auto& existing) { return existing->getRepr() == b->getRepr(); });
        
    if (count >= b->getMaxInstances()) return false;
    if (!player->CanAfford(b->getCost())) return false;

    player->Spend(b->getCost());
    buildings.push_back(b);
    return true;
}

void Board::SpawnEnemy() {
    if (!enemiesEnabled) return;
    
    Position spawnPos;
    int side = std::rand() % 4;
    
    switch (side) {
        case 0: spawnPos = Position(std::rand() % sizeX, 0); break;
        case 1: spawnPos = Position(sizeX - 1, std::rand() % sizeY); break;
        case 2: spawnPos = Position(std::rand() % sizeX, sizeY - 1); break;
        case 3: spawnPos = Position(0, std::rand() % sizeY); break;
    }
    
    if (std::rand() % 10 < 3) {
        AddEnemy(std::make_shared<Bomberman>(spawnPos));
    } else {
        AddEnemy(std::make_shared<Raider>(spawnPos));
    }
}

void Board::UpdateAll() {
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime).count();
    
    if (elapsedTime >= 15 && !enemiesEnabled) {
        enemiesEnabled = true;
    }
    
    for (auto it = buildings.begin(); it != buildings.end(); ) {
        (*it)->Update(*this);
        if ((*it)->getHealth() <= 0 && (*it)->getRepr() != "🏛") {
            it = buildings.erase(it);
        } else {
            ++it;
        }
    }
    
    for (auto it = npcs.begin(); it != npcs.end(); ) {
        (*it)->Update(*this);
        if ((*it)->getHealth() <= 0) {
            it = npcs.erase(it);
        } else {
            ++it;
        }
    }
    
    for (auto it = friendlyUnits.begin(); it != friendlyUnits.end(); ) {
        (*it)->Update(*this);
        if ((*it)->getHealth() <= 0) {
            it = friendlyUnits.erase(it);
        } else {
            ++it;
        }
    }
    
    if (enemiesEnabled) {
        updatesSinceLastEnemy++;
        
        int spawnRate = std::max(5, 30 - enemyCounter/2);
        
        if (updatesSinceLastEnemy >= spawnRate) {
            updatesSinceLastEnemy = 0;
            int enemiesToSpawn = 1 + enemyCounter / 20;
            for (int i = 0; i < enemiesToSpawn; i++) {
                SpawnEnemy();
            }
        }
    }
}

void Board::Display() const {
    system("clear");
    std::cout << "Gold 💰: " << player->getResources().getGold()
              << " | Elixir 🧪: " << player->getResources().getElixir()
              << " | Ennemis: " << npcs.size()
              << " | Allies: " << friendlyUnits.size()
              << " | Total ennemis: " << enemyCounter << "\n";
              
    if (townHall) {
        std::cout << "TownHall 🏛: " << townHall->getHealth() << "/500 HP\n";
    }
    
    if (!enemiesEnabled) {
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - gameStartTime).count();
        int remainingTime = std::max(0, 15 - (int)elapsedTime);
        std::cout << "Les ennemis arriveront dans: " << remainingTime << " secondes\n";
    }

    std::cout << '+' << std::string(sizeX * 2, '-') << "+\n";
    for (int y = 0; y < sizeY; ++y) {
        std::cout << '|';
        for (int x = 0; x < sizeX; ++x) {
            Position p(x, y);
            bool shown = false;

            if (player->getPosition() == p) { std::cout << "🏃"; shown = true; }
            
            for (auto& npc : npcs)
                if (!shown && npc->getPosition() == p) { std::cout << npc->getRepr(); shown = true; }
            
            for (auto& unit : friendlyUnits)
                if (!shown && unit->getPosition() == p) { std::cout << unit->getRepr(); shown = true; }

            for (auto& b : buildings) {
                if (!shown && b->getRepr() == "🧱" && b->isInside(p)) {
                    std::cout << "🧱";
                    shown = true;
                }
                else if (!shown && b->getHasCorners() && b->isCorner(p)) {
                    std::cout << "+ ";
                    shown = true;
                }
                else if (!shown && b->getHasCorners() && b->isOnBorder(p)) {
                    std::cout << "--";
                    shown = true;
                }
                else if (!shown && b->isCenter(p)) {
                    std::cout << b->getRepr();
                    shown = true;
                }
                else if (!shown && b->isInside(p) && !b->isCenter(p) && !b->isOnBorder(p)) {
                    std::cout << "  ";
                    shown = true;
                }
            }

            if (!shown) std::cout << "  ";
        }
        std::cout << "|\n";
    }
    std::cout << '+' << std::string(sizeX * 2, '-') << "+\n";

    std::cout << "\nCONTROLS:\n";
    std::cout << "Arrows: Move  |  G: GoldMine 💰  |  E: ElixirCollector 🧪\n";
    std::cout << "W: Wall 🧱  |  B: Barracks 🏕  |  T: Train Barbarian ⚔️ (20 Elixir)  |  A: Train Archer 🏹 (40 Elixir)\n";
    std::cout << "C: Collect  |  Q: Quit\n";

    if (IsGameOver()) {
        std::cout << "\n\nGAME OVER - Your TownHall was destroyed!\n";
    }
}
