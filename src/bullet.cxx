#include "engine/locator.hxx"
#include "engine/die.hxx"
#include "bullet.hxx"
#include "bounds.hxx"

map<string, shared_ptr<BaseBounds>> preset_bounds;
void init_bounds() {
    preset_bounds["cbullet.png"] = shared_ptr<BaseBounds>(new Circle(7, 7, 3));
}

SprBounds get_bounds(string path) {
    auto it = preset_bounds.find(path);

    if (it == preset_bounds.end()) {
        die("Error! Couldn't load preset bounds for: %s\n", path);
    }
    SprBounds res{ create_sprite(it->first), shared_ptr<BaseBounds>(it->second->clone()) };
    return res;
}

Bullet::Bullet(string id, FPoint start, bool hit_monster) : pos(start), is_dead(false),
    hit_monster(hit_monster)
{
    SprBounds sb = get_bounds(id);
    spr = sb.spr;
    bounds = sb.bounds;
    bounds->set_pos(start.x, start.y);
    assert(bounds != nullptr);
}

void Bullet::draw(sf::RenderWindow &w) {
    D_.set_key("bullet", fmt("%f, %f", pos.x, pos.y));
    Circle *c = dynamic_cast<Circle*>(bounds.get());
    D_.set_key("bounds", fmt("%f, %f", c->x, c->y));
    spr.setPosition(pos);
    w.draw(spr);
    bounds->draw(w);
}

VelBullet::VelBullet(string path, float speed, FPoint dir, FPoint start, bool hit_monster) :
    Bullet(path, start, hit_monster), speed(speed), dir(dir) { }

void VelBullet::update(const sf::Time &dt) {
    pos = pos + vel(dt.asSeconds());
    bounds->set_pos(pos.x, pos.y);
}
FPoint VelBullet::vel(float dt) const {
    return dir.normalize() * speed * dt;
}

FunBullet::FunBullet(string path, float speed, FPoint start, function<float(float)> xf,
        function<float(float)> yf, bool hit_monster) :
    Bullet(path, start, hit_monster),
    speed(speed), start(start),
    xf(xf), yf(yf)
{

}

void FunBullet::update(const sf::Time &) {
    float t = elapsed.getElapsedTime().asSeconds();
    pos = start;
    float dx = xf(t);
    float dy = yf(t);
    pos.x += dx;
    pos.y += dy;
    bounds->set_pos(pos.x, pos.y);
}

