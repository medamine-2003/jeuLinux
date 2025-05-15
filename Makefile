CXX = g++
CXXFLAGS = -std=c++14 $(shell pkg-config --cflags sdl2 SDL2_image SDL2_ttf SDL2_mixer) -I. -IBuildings -IEntities -Wall -Wextra
LDFLAGS = $(shell pkg-config --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer) -lncurses
TARGET = game

SRCS = main.cpp Board.cpp Position.cpp Resources.cpp \
       Buildings/Barracks.cpp Buildings/Building.cpp Buildings/ElixirCollector.cpp \
       Buildings/GoldMine.cpp Buildings/ResourceGenerator.cpp Buildings/TownHall.cpp \
       Buildings/Wall.cpp \
       Entities/Entity.cpp Entities/Npc.cpp Entities/Player.cpp \
       Entities/Enemies/Bomberman.cpp Entities/Enemies/Enemy.cpp Entities/Enemies/Raider.cpp \
       Entities/Troops/Archer.cpp Entities/Troops/Barbarian.cpp Entities/Troops/Troop.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
