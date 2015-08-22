#pragma once

#include "engine/butler.hxx"
#include "engine/pos.hxx"

class Bullet {
public:
    Bullet(string path, FPoint start);
    virtual ~Bullet() {}

    virtual void update(const sf::Time &dt) = 0;
    void draw(sf::RenderWindow &w);

    sf::Sprite spr;
    FPoint pos;

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

