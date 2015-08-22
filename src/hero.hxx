#pragma once

#include "engine/butler.hxx"
#include "engine/pos.hxx"

class Hero {
public:
    Hero();

    void set_pos(FPoint pos);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    sf::Sprite spr;
    IPoint move_dir;
    FPoint pos;
};

