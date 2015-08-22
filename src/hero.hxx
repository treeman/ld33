#pragma once

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "bullet.hxx"

class World;

class Hero {
public:
    Hero(World &world);

    void set_pos(FPoint pos);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
    void move_stop();

    void fire_bullets(vector<Bullet*> bullets);
    void fire();

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    sf::Sprite spr;
    IPoint move_dir;
    FPoint pos;

    World &world;

    sf::Clock fire_delay;
};

