#include <vector>
using namespace std;

#include "engine/locator.hxx"
#include "engine/pos.hxx"
#include "ai.hxx"

AI::AI(shared_ptr<Hero> hero, World &world) : hero(hero), world(world) {
    monster = world.monster; // :)
}

void AI::update(const sf::Time &dt) {
    hero->move_stop(); // Reset
    hero->fire(); // Always fire!

    // Always try to be below?
    //IPoint below = below_dir();
    //if (below != IPoint::zero) {
        //if (below.x > 0) hero->move_right();
        //else hero->move_left();
    //}

    // XXX
    // Could project all bullet paths
    // and try to avoid all paths?

    // Find all bullets close to us
    vector<shared_ptr<Bullet>> close;
    for (auto b : world.bullets) {
        if (!b->hit_monster) {
            if (in_proximity(b)) {
                close.push_back(b);
            }
        }
    }
    D_.tmp(fmt("%d bullets close", close.size()));

    const FPoint center(46 + hero->pos.x, 35 + hero->pos.y); // Yeah, almost ^^

    if (close.size() > 0) {
        shared_ptr<Bullet> closest;
        float min_dist = numeric_limits<float>::max();
        for (auto b : close) {
            const float dist = center.dist(b->center());
            if (dist < min_dist) {
                min_dist = dist;
                closest = b;
            }
        }

        // XXX This will move in the opposite direction of the bullet, could move in a better way?
        FPoint dir = closest->center() - center;
        hero->move(-dir);
        SD_.line(center, closest->center());
    }
}

bool AI::projected_to_hit(shared_ptr<Bullet> b) {
    // XXX smarter
    return hero->proximity_bound.intersects(b->bounds.get());
}

bool AI::in_proximity(shared_ptr<Bullet> b) {
    return hero->proximity_bound.intersects(b->bounds.get());
}

IPoint AI::below_dir() {
    // Recalibrate for profit
    //const float mleft = monster->pos.x + 24;
    //const float mright = monster->pos.x + 306;
    const float mleft = monster->pos.x + 24 + 30;
    const float mright = monster->pos.x + 306 - 30;
    const float x = hero->pos.x + 42;
    //D_.tmp(fmt("x: %f in %f - %f", x, mleft, mright));

    IPoint res;
    if (x <= mleft) res.x = 1;
    if (x >= mright) res.x = -1;
    return res;
}

