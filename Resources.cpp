#include "Resources.h"

Resources::Resources(int g, int e) : gold(g), elixir(e) {}

int Resources::getGold() const { return gold; }
int Resources::getElixir() const { return elixir; }

void Resources::Add(const Resources& r) { 
    gold += r.getGold(); 
    elixir += r.getElixir(); 
}

void Resources::Spend(const Resources& r) { 
    gold -= r.getGold(); 
    elixir -= r.getElixir(); 
}

bool Resources::CanAfford(const Resources& r) const { 
    return gold >= r.getGold() && elixir >= r.getElixir(); 
}