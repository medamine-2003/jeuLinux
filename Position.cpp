#include "Position.h"
#include <cstdlib>  // For abs() function

Position::Position(int x, int y) : x(x), y(y) {}

bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

int Position::Distance(const Position& other) const {
    return abs(x - other.x) + abs(y - other.y);
}
