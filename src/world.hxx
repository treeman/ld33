#pragma once

#include <vector>
using namespace std;

#include "tile.hxx"
#include "monster.hxx"
#include "hero.hxx"
#include "bullet.hxx"
#include "bulletspawner.hxx"

class World {
public:
    World(sf::RenderWindow &w);

    void handle_input(const sf::Event &e);

    void update(const sf::Time &dt);
    void draw();

    void add_bullet(shared_ptr<Bullet> bullet);
    void add_spawner(shared_ptr<Bulletspawner> spawner);
private:
    sf::RenderWindow &window;
    shared_ptr<Monster> monster;
    vector<shared_ptr<Hero>> heroes;
    vector<shared_ptr<Bullet>> bullets;
    vector<shared_ptr<Bulletspawner>> spawners;
};

