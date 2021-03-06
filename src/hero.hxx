#pragma once

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "bullet.hxx"
#include "bounds.hxx"

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
    void move(FPoint dir);

    void fire_bullets(vector<Bullet*> bullets);
    void fire();

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);

    bool is_collision(shared_ptr<BaseBounds> b);

    Circle proximity_bound;
    Rect proximity_rect;

    sf::Sprite spr;
    FPoint move_dir;
    FPoint pos;

    World &world;

    sf::Clock fire_delay;

    Bounds bounds;
    Bounds shield_bounds;

    void hit();
    sf::Sprite heart, empty_heart;
    int life;
    bool is_dead;

    float shield_load; // 0 <- 1
    sf::Sprite shield_status;
    sf::Sprite shield_status_loading;
    sf::Sprite shield;

    sf::Sound die_snd, shield_snd;
};

