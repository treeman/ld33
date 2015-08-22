#pragma once

#include "engine/pos.hxx"

class Tile {
public:
    Tile();

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);

    FPoint pos;
    sf::Sprite spr;
};

