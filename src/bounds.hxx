#pragma once

#include <memory>
#include "engine/pos.hxx"

struct BaseBounds {
    virtual ~BaseBounds() {};

    virtual BaseBounds *clone() = 0;

    virtual void draw(sf::RenderWindow &w, FPoint offset) = 0;
};

// Offset from 0, recalculate later offset to pos
struct Rect : public BaseBounds {
    Rect(float x1, float y1, float x2, float y2);
    BaseBounds *clone() override;

    void draw(sf::RenderWindow &w, FPoint offset) override;

    float x, y, w, h;
private:
    sf::RectangleShape shape;
};

// x/y specifies center. Is this good? Whatever!
struct Circle : public BaseBounds {
    Circle(float x, float y, float r);
    BaseBounds *clone() override;

    void draw(sf::RenderWindow &w, FPoint offset) override;

    float x, y, r;
private:
    sf::CircleShape shape;
};

// Composed of rectangles/circles
class Bounds {
public:
    Bounds();

    void add_rect(float x1, float y1, float x2, float y2);
    void add_circle(float x, float y, float r);
    void set_pos(FPoint pos);
    void move(FPoint dp);

    void draw(sf::RenderWindow &w);

    FPoint pos;

    vector<shared_ptr<BaseBounds>> bounds;
};

