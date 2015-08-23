#pragma once

#include <memory>
#include "engine/pos.hxx"

class Rect;
class Circle;

struct BaseBounds {
    virtual ~BaseBounds() {};

    virtual BaseBounds *clone() = 0;
    virtual bool is_inside(float x, float y) = 0;

    virtual bool intersects_rect(Rect *r) = 0;
    virtual bool intersects_circle(Circle *c) = 0;
    virtual bool intersects(BaseBounds *b) = 0;

    virtual void draw(sf::RenderWindow &w) = 0;

    virtual FPoint center() const = 0;
    void set_pos(float x, float y) { orig.x = x; orig.y = y; }
    void move(float x, float y) { orig.x += x; orig.y += y; }

    FPoint orig;
};

// Offset from 0, recalculate later offset to pos
struct Rect : public BaseBounds {
    Rect(float x1, float y1, float x2, float y2);
    BaseBounds *clone() override;

    bool is_inside(float x, float y) override;
    bool intersects_rect(Rect *r) override;
    bool intersects_circle(Circle *c) override;
    bool intersects(BaseBounds *b) override;

    void draw(sf::RenderWindow &w) override;

    FPoint center() const override;

    float x, y, w, h;

    sf::RectangleShape shape;
};

// x/y specifies center. Is this good? Whatever!
struct Circle : public BaseBounds {
    Circle(float x, float y, float r);
    BaseBounds *clone() override;

    bool is_inside(float x, float y) override;
    bool intersects_rect(Rect *r) override;
    bool intersects_circle(Circle *c) override;
    bool intersects(BaseBounds *b) override;

    void draw(sf::RenderWindow &w) override;

    FPoint center() const override;

    float x, y, r;

    sf::CircleShape shape;
};

// Composed of rectangles/circles
class Bounds {
public:
    Bounds();

    void add_rect(float x1, float y1, float x2, float y2);
    void add_circle(float x, float y, float r);
    void set_pos(FPoint pos);

    void draw(sf::RenderWindow &w);

    bool intersects(shared_ptr<BaseBounds> b);

    FPoint pos;

    vector<shared_ptr<BaseBounds>> bounds;
};

