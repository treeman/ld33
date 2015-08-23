#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "engine/rand.hxx"
#include "world.hxx"

const int tile_width = 32;
const int x_tiles = 20;
const int y_tiles = 15;

World::World(sf::RenderWindow &w, int num_heroes) : window(w) {
    monster.reset(new Monster(*this));
    for (int i = 0; i < num_heroes; ++i) {
        auto hero = shared_ptr<Hero>(new Hero(*this));
        hero->set_pos(FPoint(rand_int(100, 500), 510));
        heroes.push_back(hero);
    }
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
        if (p.x < -10 || p.x > 810) x->is_dead = true;
        if (p.y < -10 || p.y > 810) x->is_dead = true;

        if (x->hit_monster) {
            if (monster->is_collision(x->bounds)) {
                x->is_dead = true;
                monster->take_damage(1);
            }
        }
        else {
            for (auto h : heroes) {
                if (h->is_collision(x->bounds)) {
                    x->is_dead = true;
                    h->hit();
                }
            }
        }
    }
    // Need to kill of things
    spawners.erase(remove_if(spawners.begin(),
                            spawners.end(),
                            [](shared_ptr<Bulletspawner> x) { return x->is_dead; }),
                  spawners.end());
    bullets.erase(remove_if(bullets.begin(),
                            bullets.end(),
                            [](shared_ptr<Bullet> b) { return b->is_dead; }),
                  bullets.end());
    heroes.erase(remove_if(heroes.begin(),
                           heroes.end(),
                           [](shared_ptr<Hero> x) { return x->is_dead; }),
                 heroes.end());

    //D_.tmp(fmt("Tracking %d bullets\n", bullets.size()));
    //D_.tmp(fmt("And %d spawners\n", spawners.size()));
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

