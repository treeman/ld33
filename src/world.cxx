#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "world.hxx"

const int tile_width = 32;
const int x_tiles = 20;
const int y_tiles = 15;

World::World(sf::RenderWindow &w) : window(w) {
    monster.reset(new Monster(*this));
    auto hero = shared_ptr<Hero>(new Hero(*this));
    hero->set_pos(FPoint(380, 510));
    heroes.push_back(hero);
}

void World::handle_input(const sf::Event &e) {
    monster->handle_input(e);
}

void World::update(const sf::Time &dt) {
    monster->update(dt);

    for (auto x : heroes)
        x->update(dt);
    for (auto x : spawners)
        x->update(dt);
    for (auto x : bullets) {
        x->update(dt);

        FPoint p = x->pos;
        if (p.x < -10 || p.x > 810) x->dead = true;
        if (p.y < -10 || p.y > 810) x->dead = true;
    }
    // Need to kill of things
    spawners.erase(remove_if(spawners.begin(),
                            spawners.end(),
                            [](shared_ptr<Bulletspawner> x) { return x->dead; }),
                  spawners.end());
    bullets.erase(remove_if(bullets.begin(),
                            bullets.end(),
                            [](shared_ptr<Bullet> b) { return b->dead; }),
                  bullets.end());

    D_.tmp(fmt("Tracking %d bullets\n", bullets.size()));
    D_.tmp(fmt("And %d spawners\n", spawners.size()));
}

void World::draw() {
    window.clear(sf::Color(0xffffffff));
    monster->draw(window);
    for (auto x : heroes)
        x->draw(window);
    for (auto x : bullets)
        x->draw(window);
}

void World::add_bullet(shared_ptr<Bullet> bullet) {
    bullets.push_back(bullet);
}

void World::add_spawner(shared_ptr<Bulletspawner> spawner) {
    spawners.push_back(spawner);
}

