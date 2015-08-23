#pragma once

#include "engine/pos.hxx"
#include "angles.hxx"

class World;

class Bulletspawner {
public:
    Bulletspawner(World &w, string bullet);

    void update(const sf::Time &dt);

    // Set base position of the spawner
    void set_pos(FPoint p);
    void move(FPoint dv);

    // Add bullet generators
    void add(float angle, float speed, float delay);

    bool is_dead;
private:
    World &world;

    struct Info {
        float angle, speed, delay;
    };
    vector<Info> to_generate;
    FPoint pos;
    sf::Clock elapsed;
    string bullet;
};

// Speed
// Rotation (direction)
// Delay
// Start (x, y)
// Acceleration?

