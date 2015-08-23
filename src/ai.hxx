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

    bool projected_to_hit(shared_ptr<Bullet> b);
    bool in_proximity(shared_ptr<Bullet> b);
    IPoint below_dir(); // How to move if we want to be below?
};

