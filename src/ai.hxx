#pragma once

#include "world.hxx"

// It's happening!!!
class AI {
public:
    AI(shared_ptr<Hero> hero, World &world);

    void update(const sf::Time &dt);
private:
    shared_ptr<Hero> hero;
    shared_ptr<Monster> monster;
    World &world;

    bool projected_to_hit(shared_ptr<Bullet> b, float dt);
    bool in_proximity(shared_ptr<Bullet> b);
    IPoint below_dir(); // How to move if we want to be below?

    void random_walk(float dt);
    float rand_angle;
    //float rand_angle_vel;
    //float rand_angle_acc;
    sf::Clock rand_clock;
    float rand_time;

    // These do not do anything if they have to
    void move_below(float dt);
    void avoid_bullets(float dt);
    void avoid_monster(float dt);
};

