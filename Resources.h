#ifndef RESOURCES_H
#define RESOURCES_H

class Resources {
    int gold, elixir;
public:
    Resources(int g = 0, int e = 0);
    int getGold() const;
    int getElixir() const;
    void Add(const Resources& r);
    void Spend(const Resources& r);
    bool CanAfford(const Resources& r) const;
};

#endif // RESOURCES_H