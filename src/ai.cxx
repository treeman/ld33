#include <vector>
using namespace std;

#include "engine/locator.hxx"
#include "engine/pos.hxx"
#include "engine/lines.hxx"
#include "engine/rand.hxx"
#include "ai.hxx"

AI::AI(shared_ptr<Hero> hero, World &world) : hero(hero), world(world) {
    monster = world.monster; // :)
    rand_angle = 270;
    //rand_angle_vel = 0;
    //rand_angle_acc = 0;
    //rand_choice = 0;
    rand_time = 0;
    L_("Constructing...\n");
}

void AI::update(const sf::Time &_dt) {
    const float dt = _dt.asSeconds();

    hero->move_stop(); // Reset
    hero->fire(); // Always fire!

    random_walk(dt);   // Make some random movements?
    move_below(dt);    // If we're not doing anything, try be below monster
    avoid_bullets(dt); // If bullets are projected to hit us, try to avoid!!
    avoid_monster(dt); // If we are to close to the monster
}

bool AI::projected_to_hit(shared_ptr<Bullet> b, float dt) {
    VelBullet *x = dynamic_cast<VelBullet*>(b.get());
    if (x == nullptr) return false; // Cannot predict

    FPoint p1 = x->pos;
    FPoint vel = x->vel(dt);
    FPoint p2 = p1 + vel * 1000;
    FLineSegment l(p1, p2);
    //SD_.line(p1, p2);
    return hero->proximity_rect.intersects(l);
}

bool AI::in_proximity(shared_ptr<Bullet> b) {
    return hero->proximity_bound.intersects(b->bounds.get());
}

IPoint AI::below_dir() {
    // Recalibrate for profit
    const float mleft = monster->pos.x + 24 + 30;
    const float mright = monster->pos.x + 306 - 30;
    const float x = hero->pos.x + 42;

    IPoint res;
    if (x <= mleft) res.x = 1;
    if (x >= mright) res.x = -1;
    return res;
}

// A regular random walk is too irregular
void AI::random_walk(float dt) {
    //if (rand_int(0, 1) == 1) rand_angle_acc = 5000;
    //else rand_angle_acc = -5000;
    //rand_angle_vel += rand_angle_acc;
    //rand_angle += rand_angle_vel * dt;
    //rand_angle = rand_angle + rand_int(-1, 1);

    //D_.tmp(fmt("acc: %f", rand_angle_acc));
    //D_.tmp(fmt("val: %f", rand_angle_vel));
    //D_.tmp(fmt("ang: %f", rand_angle));
    //
    //D_.tmp(fmt("dt: %f", dt));

    //rand_time = rand_time + dt;
    //if (rand_time >= 1.0) {
        ////rand_angle = rand_int(0, 360);
        ////rand_time = 0;
    //}
    //D_.tmp(fmt("clock: %f", rand_time));

    if (rand_clock.getElapsedTime().asSeconds() >= 0.5) {
        rand_angle = rand_angle + rand_int(-120, 120);
        rand_clock.restart();
    }

    /*
    //rand_choice += dt;
    if (rand_clock.getElapsedTime().asSeconds() >= 1.0) {
        rand_clock.restart();
        rand_angle = rand_int(0, 360);
        rand_clock.restart();
        //rand_choice.restart();
        //L_("angle: %f now time: %f\n", rand_angle, rand_clo);
        //rand_choice = 0;
    }
    */

    //rand_angle += rand_int(-5, 5);
    FPoint dir = angle2dir(rand_angle);
    hero->move(dir);

    // Visualize it...
    //FPoint p = hero->pos;
    //const float r = 50;
    //shared_ptr<sf::CircleShape> c(new sf::CircleShape(r));
    //c->setOrigin(r, r);
    //c->setPosition(p);
    //SD_.line(p, p + dir.normalize() * r);
    //SD_.add(c);
}
void AI::move_below(float dt) {
    // Always try to be below?
    IPoint below = below_dir();
    if (below != IPoint::zero) {
        if (below.x > 0) hero->move_right();
        else hero->move_left();
    }
}
void AI::avoid_bullets(float dt) {
    // Find all bullets close to us
    vector<shared_ptr<Bullet>> close;
    for (auto b : world.bullets) {
        if (!b->hit_monster) {
            if (in_proximity(b)) {
                close.push_back(b);
            }
        }
    }
    //D_.tmp(fmt("%d bullets close", close.size()));

    const FPoint center(46 + hero->pos.x, 35 + hero->pos.y); // Yeah, almost ^^

    if (close.size() > 0) {
        shared_ptr<Bullet> closest;
        float min_dist = numeric_limits<float>::max();
        for (auto b : close) {
            if (projected_to_hit(b, dt)) {
                //SD_.line(b->center(), center);
                const float dist = center.dist(b->center());
                if (dist < min_dist) {
                    min_dist = dist;
                    closest = b;
                }
            }
        }

        // Opposite seems to be a little bit better.

        // Move into opposite direction
        if (closest != nullptr) {
            FPoint dir = closest->center() - center;
            hero->move(-dir);
            SD_.line(center, closest->center());
        }

        // Move in perpendicular direction
        //if (closest != nullptr) {
            //FPoint dir = closest->center() - center;
            //FPoint to(-dir.y, dir.x);
            //hero->move(to);
            //SD_.line(center, closest->center());
            //SD_.line(center, center + to * 100);
        //}
    }
}

void AI::avoid_monster(float dt) {
    float monster_y = monster->pos.y + monster->height;
    if (hero->pos.y < monster_y) {
        D_.tmp("monster collision!");
        hero->move_down();
    }
}

