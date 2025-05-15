#include "GoldMine.h"

GoldMine::GoldMine(Position p) 
    : ResourceGenerator(p, 3, 3, "💰", "🪙", 
                      Resources(0, 100), 3, 
                      Resources(5, 0), 150) {}