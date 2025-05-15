#ifndef POSITION_H
#define POSITION_H

class Position {
public:
    int x, y;
    Position(int x = 0, int y = 0);
    bool operator==(const Position& other) const;
    int Distance(const Position& other) const;
};

#endif // POSITION_H