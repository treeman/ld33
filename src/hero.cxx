#include "engine/locator.hxx"
#include "hero.hxx"
#include "bullet.hxx"
#include "world.hxx"

const float move_speed = 300;
const int width = 85;
const int height = 87;

Hero::Hero(World &world) : world(world) {
    spr = create_sprite("hero.png");
}

void Hero::set_pos(FPoint _pos) {
    pos = _pos;
    // TODO better hitbox
    if (pos.x < 0) pos.x = 0;
    if (pos.x + width > 800) pos.x = 800 - width;
    if (pos.y < 200) pos.y = 200;
    if (pos.y + height > 600) pos.y = 600 - height;

    D_.tmp(fmt("hero pos: %f, %f", pos.x, pos.y));
    spr.setPosition(pos);
}

void Hero::move_left() {
    move_dir.x = -1;
}
void Hero::move_right() {
    move_dir.x = 1;
}
void Hero::move_up() {
    move_dir.y = -1;
}
void Hero::move_down() {
    move_dir.y = 1;
}
void Hero::move_stop() {
    move_dir.x = 0;
    move_dir.y = 0;
}

void Hero::fire_bullets(vector<Bullet*> bullets) {
    for (auto x : bullets) {
        shared_ptr<Bullet> b(x);
        b->pos = b->pos + pos;
        world.add_bullet(b);
    }
}

void Hero::fire() {
    if (fire_delay.getElapsedTime().asSeconds() > 0.02) {
        string path = "cbullet.png";
        vector<Bullet*> bullets = {
            new VelBullet(path, 800, FPoint(0, -1), FPoint(42, 10), true),
        };
        fire_bullets(bullets);
        fire_delay.restart();
    }
}

void Hero::update(const sf::Time &dt) {
    FPoint dv = FPoint(move_dir).normalize() * move_speed * dt.asSeconds();
    pos = pos + dv;
    set_pos(pos);
}

void Hero::draw(sf::RenderWindow &w) {
    w.draw(spr);
}

