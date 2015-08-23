#include "engine/locator.hxx"
#include "bulletspawner.hxx"
#include "world.hxx"
#include "bullet.hxx"

Bulletspawner::Bulletspawner(World &w) : is_dead(false), world(w) { }

void Bulletspawner::update(const sf::Time &) {
    float t = elapsed.getElapsedTime().asSeconds();
    for (auto it = to_generate.begin(); it != to_generate.end(); ++it) {
        if (it->delay < t) {
            world.add_bullet(shared_ptr<Bullet>(new VelBullet(
                "cbullet.png", // TODO fix
                it->speed,
                angle2dir(it->angle),
                pos,
                false // TODO only targets hero
            )));
        }
    }
    // Remove newly generated ones
    to_generate.erase(remove_if(to_generate.begin(),
                                to_generate.end(),
                                [t](Info x) { return x.delay < t; }),
                      to_generate.end());
    is_dead = to_generate.empty();
}

// Set base position of the spawner
void Bulletspawner::set_pos(FPoint p) { pos = p; }
void Bulletspawner::move(FPoint dv) { set_pos(pos + dv); }

// Add bullet generators
void Bulletspawner::add(float angle, float speed, float delay) {
    to_generate.push_back(Info { angle, speed, delay });
}

