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

Bullet::Bullet(string id, FPoint start) : pos(start), dead(false)
{
    SprBounds sb = get_bounds(id);
    spr = sb.spr;
    bounds = sb.bounds;
    assert(bounds != nullptr);
}

void Bullet::draw(sf::RenderWindow &w) {
    spr.setPosition(pos);
    w.draw(spr);
    bounds->draw(w, pos);
}

VelBullet::VelBullet(string path, float speed, FPoint dir, FPoint start) : Bullet(path, start),
    speed(speed), dir(dir) {
}

void VelBullet::update(const sf::Time &dt) {
    FPoint dv = dir.normalize() * speed * dt.asSeconds();
    pos = pos + dv;
}

FunBullet::FunBullet(string path, float speed, FPoint start, function<float(float)> xf,
    function<float(float)> yf) : Bullet(path, start), speed(speed), start(start),
    xf(xf), yf(yf)
{

}

void FunBullet::update(const sf::Time &) {
    float t = elapsed.getElapsedTime().asSeconds();
    pos = start;
    pos.x += xf(t);
    pos.y += yf(t);
}

