#include "engine/locator.hxx"
#include "hero.hxx"
#include "bullet.hxx"
#include "world.hxx"

const float move_speed = 300;
const int width = 85;
const int height = 87;

Hero::Hero(World &world) : proximity_bound(48, 48, 150), proximity_rect(18, 18, 82, 94),
        world(world)
{
    spr = create_sprite("hero.png");

    bounds.add_rect(22, 20, 75, 90);
    shield_bounds.add_circle(51, 50, 47);
    proximity_bound.shape.setFillColor(sf::Color(0xA1D49011));
    proximity_bound.shape.setOutlineColor(sf::Color(0x9739A3FF));
    proximity_rect.shape.setFillColor(sf::Color(0xA1D49011));
    proximity_rect.shape.setOutlineColor(sf::Color(0x9739A3FF));

    heart = create_sprite("heart.png");
    empty_heart = create_sprite("empty_heart.png");
    life = 4;
    is_dead = false;

    //shield_load = 1;
    shield_load = 0.4;
    shield_status = create_sprite("shieldstatus.png");
    shield_status_loading = create_sprite("shieldstatus_loading.png");
    shield = create_sprite("shield.png");
}

void Hero::set_pos(FPoint _pos) {
    pos = _pos;
    // TODO better hitbox
    if (pos.x < 0) {
        pos.x = 0;
        if (move_dir.x < 0) move_dir.x = 0;
    }
    if (pos.x + width > 800) {
        pos.x = 800 - width;
        if (move_dir.x > 0) move_dir.x = 0;
    }
    if (pos.y < 200) {
        pos.y = 200;
        if (move_dir.y > 0) move_dir.y = 0;
    }
    if (pos.y + height > 600) {
        pos.y = 600 - height;
        if (move_dir.y < 0) move_dir.y = 0;
    }

    //D_.tmp(fmt("hero pos: %f, %f", pos.x, pos.y));
    spr.setPosition(pos);
    bounds.set_pos(pos);
    shield_bounds.set_pos(pos);
    proximity_bound.set_pos(pos.x, pos.y);
    proximity_rect.set_pos(pos.x, pos.y);
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
void Hero::move(FPoint dir) {
    move_dir = dir;
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
            new VelBullet(path, 800, FPoint(0, -1), FPoint(16, 40), true),
            new VelBullet(path, 800, FPoint(0, -1), FPoint(64, 40), true),
        };
        fire_bullets(bullets);
        fire_delay.restart();
    }
}

void Hero::update(const sf::Time &dt) {
    FPoint dv = move_dir.normalize() * move_speed * dt.asSeconds();
    //FPoint cpos = proximity_rect.center();
    //SD_.line(cpos, cpos + dv * 100);

    if (shield_load < 1)
        shield_load += dt.asSeconds() * 0.2;
    //D_.tmp(fmt("load: %f", shield_load));

    pos = pos + dv;
    set_pos(pos);
}

void Hero::draw(sf::RenderWindow &w) {
    w.draw(spr);
    //bounds.draw(w);
    //shield_bounds.draw(w);
    //proximity_bound.draw(w);
    //proximity_rect.draw(w);
    const float y = pos.y + 84;
    const float left_x = pos.x + 10;
    for (int i = 0; i < 4; ++i) {
        sf::Sprite *s = nullptr;
        if (life > i) s = &heart;
        else s = &empty_heart;

        s->setPosition(left_x + 18 * i, y);
        w.draw(*s);
    }

    const FPoint shield_pos(pos.x + 85, pos.y + 25);

    if (shield_load < 1) {
        shield_status_loading.setPosition(shield_pos);
        shield_status_loading.setScale(1, shield_load);
        w.draw(shield_status_loading);
    }
    else {
        shield_status.setPosition(shield_pos);
        w.draw(shield_status);
        shield.setPosition(pos);
        w.draw(shield);
    }
}

bool Hero::is_collision(shared_ptr<BaseBounds> b) {
    if (shield_load >= 1) return bounds.intersects(b);
    else return shield_bounds.intersects(b);
}

void Hero::hit() {
    if (shield_load >= 1) {
        shield_load = 0;
    }
    else {
        life -= 1;
        if (life <= 0) {
            is_dead = true;
            life = 0;
        }
    }
}

