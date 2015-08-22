#pragma once

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "bounds.hxx"

// Collect bounds and sprites in one
struct SprBounds {
    sf::Sprite spr;
    shared_ptr<BaseBounds> bounds;
};

void init_bounds(); // XXX smelly!
SprBounds get_bounds(string id);

class Bullet {
public:
    Bullet(string id, FPoint start);
    virtual ~Bullet() {}

    virtual void update(const sf::Time &dt) = 0;
    void draw(sf::RenderWindow &w);

    FPoint pos;
    sf::Sprite spr;
    shared_ptr<BaseBounds> bounds;

    bool dead;
};

class VelBullet : public Bullet {
public:
    VelBullet(string path, float speed, FPoint dir, FPoint start);

    void update(const sf::Time &dt) override;

    float speed;
    FPoint dir;
};

class FunBullet : public Bullet {
public:
    FunBullet(string path, float speed, FPoint start, function<float(float)> xf,
            function<float(float)> yf);

    void update(const sf::Time &dt) override;

    float speed;
    FPoint start;
    function<float(float)> xf, yf;
    sf::Clock elapsed;
};

