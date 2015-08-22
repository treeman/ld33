#include "engine/locator.hxx"
#include "hero.hxx"

const float move_speed = 300;
//const int width = 332;
//const int height = 305;

Hero::Hero() {
    spr = create_sprite("hero.png");
}

void Hero::set_pos(FPoint _pos) {
    pos = _pos;
    // TODO better hitbox
    //if (pos.x < 0) pos.x = 0;
    //if (pos.x + width > 800) pos.x = 800 - width;
    //if (pos.y < 0) pos.y = 0;
    //if (pos.y + height > 500) pos.y = 500 - height;

    D_.tmp(fmt("hero pos: %f, %f", pos.x, pos.y));
    spr.setPosition(pos);
}

void Hero::update(const sf::Time &dt) {
    //move_dir = IPoint();
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move_dir.x -= 1;
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move_dir.x += 1;
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move_dir.y -= 1;
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move_dir.y += 1;

    FPoint dv = FPoint(move_dir).normalize() * move_speed * dt.asSeconds();
    pos = pos + dv;
    set_pos(pos);
}

void Hero::draw(sf::RenderWindow &w) {
    w.draw(spr);
}

