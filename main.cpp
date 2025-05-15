#include "Board.h"
#include "Entities/Player.h"
#include "Buildings/Wall.h"
#include "Buildings/GoldMine.h"
#include "Buildings/ElixirCollector.h"
#include "Buildings/Barracks.h"
#include "Entities/Troops/Barbarian.h"
#include "Entities/Troops/Archer.h"
#include "Entities/Enemies/Raider.h"
#include "Entities/Enemies/Bomberman.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <algorithm>
#include <climits>  // For INT_MAX
#include <cstdlib>  // For abs()
#include <SDL2/SDL.h> // For future SDL integration

// Linux-specific keyboard input handling
int _kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int _getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

// SDL2 initialization (for future graphics)
bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    *window = SDL_CreateWindow("Clash of Clones", 
                              SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, 
                              800, 600, 
                              SDL_WINDOW_SHOWN);
    if (!*window) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (!*renderer) {
        SDL_DestroyWindow(*window);
        std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    return true;
}

int main() {
    // For future SDL integration
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    bool useSDL = false; // Set to true when ready to use SDL
    
    if (useSDL && !initSDL(&window, &renderer)) {
        std::cerr << "Falling back to terminal mode\n";
        useSDL = false;
    }

    // Game initialization
    const int width = 40, height = 20;
    auto player = std::make_shared<Player>(Position(width/2, height/2));
    Board board(width, height);
    board.setPlayer(player);

    bool running = true;
    while (running && !board.IsGameOver()) {
        if (useSDL) {
            // Future SDL rendering would go here
            SDL_RenderClear(renderer);
            // Render game objects...
            SDL_RenderPresent(renderer);
        } else {
            board.Display();
        }
        
        board.UpdateAll();

        if (_kbhit()) {
            int ch = _getch();
            if (ch == 27) { // Escape sequence for arrow keys
                ch = _getch(); // Skip [
                ch = _getch(); // Get actual key
                Position p = player->getPosition();
                switch (ch) {
                    case 'A': player->Move(0, -1, width, height); break; // Up
                    case 'B': player->Move(0, 1, width, height); break;  // Down
                    case 'D': player->Move(-1, 0, width, height); break; // Left
                    case 'C': player->Move(1, 0, width, height); break;  // Right
                }
            } else {
                Position p = player->getPosition();
                switch (tolower(ch)) {
                    case 'w': board.AddBuilding(std::make_shared<Wall>(p)); break;
                    case 'g': board.AddBuilding(std::make_shared<GoldMine>(p)); break;
                    case 'e': board.AddBuilding(std::make_shared<ElixirCollector>(p)); break;
                    case 'b': board.AddBuilding(std::make_shared<Barracks>(p)); break;
                    case 't': 
                        for (auto& b : board.getBuildings()) {
                            if (b->getRepr() == "🏕" && p.Distance(b->getPosition()) <= 1) {
                                if (player->getResources().getElixir() >= 20) {
                                    player->Spend(Resources(0, 20));
                                    dynamic_cast<Barracks*>(b.get())->StartTraining(0); // Barbarian
                                }
                            }
                        }
                        break;
                    case 'a': 
                        for (auto& b : board.getBuildings()) {
                            if (b->getRepr() == "🏕" && p.Distance(b->getPosition()) <= 1) {
                                if (player->getResources().getElixir() >= 40) {
                                    player->Spend(Resources(0, 40));
                                    dynamic_cast<Barracks*>(b.get())->StartTraining(1); // Archer
                                }
                            }
                        }
                        break;
                    case 'c': player->Interact(board); break;
                    case 'q': running = false; break;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Cleanup
    if (useSDL) {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    if (board.IsGameOver()) {
        board.Display();
        std::cout << "\nPress any key to exit...";
        _getch();
    }

    return 0;
}
