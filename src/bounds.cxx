#include "engine/locator.hxx"
#include "bounds.hxx"

const sf::Color outline = sf::Color(0xF294C9FF);
const sf::Color fillcol = sf::Color(0xEBCEDE22);
const float thickness = 1.0;

Rect::Rect(float x1, float y1, float x2, float y2) {
    if (x1 > x2) swap(x1, x2);
    if (y1 > y2) swap(y1, y2);
    x = x1; y = y1;
    w = x2 - x1; h = y2 - y1;

    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setFillColor(fillcol);
}
BaseBounds *Rect::clone() {
    return new Rect(*this);
}

void Rect::draw(sf::RenderWindow &window, FPoint offset) {
    shape.setPosition(offset.x + x, offset.y + y);
    shape.setSize(FPoint(w, h));
    window.draw(shape);
}

Circle::Circle(float x, float y, float r) : x(x), y(y), r(r) {
    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setFillColor(fillcol);
}
BaseBounds *Circle::clone() {
    return new Circle(x, y, r);
}

void Circle::draw(sf::RenderWindow &window, FPoint offset) {
    shape.setRadius(r);
    shape.setOrigin(r, r);
    shape.setPosition(offset.x + x, offset.y + y);
    window.draw(shape);
}

Bounds::Bounds() { }

void Bounds::add_rect(float x1, float y1, float x2, float y2) {
    bounds.push_back(shared_ptr<BaseBounds>(new Rect { x1, y1, x2, y2 }));
}
void Bounds::add_circle(float x, float y, float r) {
    bounds.push_back(shared_ptr<BaseBounds>(new Circle { x, y, r }));
}
void Bounds::set_pos(FPoint _pos) {
    pos = _pos;
}
void Bounds::move(FPoint dp) {
    pos = pos + dp;
}

void Bounds::draw(sf::RenderWindow &window) {
    for (auto x : bounds) x->draw(window, pos);
}

