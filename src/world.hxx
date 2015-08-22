#pragma once

#include <vector>
using namespace std;

#include "tile.hxx"

class World {
public:
    World(sf::RenderWindow &w);

    void update(const sf::Time &dt);
    void draw();
private:
    sf::Sprite spr;
    sf::RenderWindow &window;
    vector<vector<Tile>> tiles;
};

