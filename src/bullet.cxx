#include "engine/locator.hxx"
#include "bullet.hxx"

Bullet::Bullet(string path, FPoint start) : pos(start), 
    dead(false)
{
    spr = create_sprite(path);
}

void Bullet::draw(sf::RenderWindow &w) {
    spr.setPosition(pos);
    w.draw(spr);
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

