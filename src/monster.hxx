#pragma once

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "bullet.hxx"
#include "bulletspawner.hxx"
#include "bounds.hxx"

class World;

class Monster {
public:
    Monster(World &world);

    void set_pos(FPoint pos);
    void move(FPoint dv);

    void handle_input(const sf::Event &e);
    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    sf::Sprite spr;
    IPoint move_dir;
    FPoint pos;
    World &world;

    void fire_bullets(vector<Bullet*> bullets);
    vector<shared_ptr<Bulletspawner>> spawners;

    void fire_eyes();
    sf::Clock eyes_fire_delay;

    void fire_left();
    void fire_right();

    Bounds bounds;
};

