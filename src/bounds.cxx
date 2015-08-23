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
    shape.setSize(FPoint(w, h));
}
BaseBounds *Rect::clone() {
    return new Rect(*this);
}

bool Rect::is_inside(float _x, float _y) {
    return orig.x + x <= _x && _x <= orig.x + x + w &&
           orig.y + y <= _y && _y <= orig.y + y + h;
}


void Rect::draw(sf::RenderWindow &window) {
    FPoint p(orig.x + x, orig.y + y);
    shape.setPosition(p.x, p.y);
    window.draw(shape);
}
bool Rect::intersects(BaseBounds *b) {
    return b->intersects_rect((Rect*)this);
}
bool Rect::intersects_rect(Rect *r) {
    return !(orig.x + x     > r->orig.x + r->x + r->w ||
             orig.x + x + w < r->orig.x + r->x        ||
             orig.y + y     > r->orig.y + r->y + r->h ||
             orig.y + y + h < r->orig.y + r->y);
}
bool Rect::intersects_circle(Circle *c) {
    //return false; // TODO fix
    return is_inside(c->orig.x + c->x, c->orig.y + c->y) ||
           c->is_inside(orig.x + x,     orig.y + y) ||
           c->is_inside(orig.x + x + w, orig.y + y) ||
           c->is_inside(orig.x + x,     orig.y + y + w) ||
           c->is_inside(orig.x + x + w, orig.y + y + w);
}
bool Rect::intersects(FLineSegment l) {
    // top left, top right, bottom left, bottom right
    FPoint tl(orig.x + x,     orig.y + y);
    FPoint tr(orig.x + x + w, orig.y + y);
    FPoint bl(orig.x + x,     orig.y + y + h);
    FPoint br(orig.x + x + w, orig.y + y + h);
    if (l.intersect(FLineSegment(tl, tr)).size() > 0) return true;
    if (l.intersect(FLineSegment(tl, bl)).size() > 0) return true;
    if (l.intersect(FLineSegment(bl, br)).size() > 0) return true;
    if (l.intersect(FLineSegment(tr, br)).size() > 0) return true;
    return false;
}

FPoint Rect::center() const {
    return FPoint(orig.x + w / 2, orig.y + h / 2);
}

Circle::Circle(float x, float y, float r) : x(x), y(y), r(r) {
    shape.setOutlineColor(outline);
    shape.setOutlineThickness(thickness);
    shape.setFillColor(fillcol);
    shape.setRadius(r);
    shape.setOrigin(r, r);
}
BaseBounds *Circle::clone() {
    return new Circle(x, y, r);
}
bool Circle::intersects(BaseBounds *b) {
    return b->intersects_circle(this);
}
bool Circle::intersects_rect(Rect *r) {
    return r->intersects_circle(this);
}
bool Circle::intersects_circle(Circle *c) {
    return FPoint(orig.x + x, orig.y + y).dist(FPoint(c->orig.x + c->x, c->orig.y + c->y))
        <= r + c->r;
}

bool Circle::is_inside(float _x, float _y) {
    return FPoint(x, y).dist(FPoint(_x, _y)) <= r;
}

void Circle::draw(sf::RenderWindow &window) {
    FPoint p(orig.x + x, orig.y + y);
    shape.setPosition(p.x, p.y);
    window.draw(shape);
}

FPoint Circle::center() const {
    return FPoint(orig.x + r / 2, orig.y + r / 2);
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
    for (auto x : bounds) {
        x->set_pos(pos.x, pos.y);
    }
}
//void Bounds::move(FPoint dp) {
    //L_("Moving\n");
    //pos = pos + dp;
//}

void Bounds::draw(sf::RenderWindow &window) {
    for (auto x : bounds) x->draw(window);
}

bool Bounds::intersects(shared_ptr<BaseBounds> b) {
    return intersects(b.get());
}
bool Bounds::intersects(BaseBounds *b) {
    // Yeah it's slow. Meh :)
    for (auto x : bounds) if (x->intersects(b)) return true;
    return false;
}

