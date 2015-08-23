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

    bool is_collision(shared_ptr<BaseBounds> bounds);

    sf::Sprite spr;
    IPoint move_dir;
    FPoint pos;
    World &world;

    void fire_bullets(vector<Bullet*> bullets);
    vector<shared_ptr<Bulletspawner>> spawners;

    void fire_eyes();
    sf::Clock eyes_delay;

    void fire_left();
    sf::Clock left_delay;

    void fire_right();
    sf::Clock right_delay;

    Bounds bounds;

    float monster_life;
    float max_monster_life;

    void take_damage(float damage);

    bool is_dead;

    const float move_speed = 300;
    const int width = 332;
    const int height = 305;
};

