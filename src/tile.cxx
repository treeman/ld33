#include "engine/butler.hxx"
#include "tile.hxx"

Tile::Tile() {
    spr = create_sprite("tst.png");
}

void Tile::update(const sf::Time &dt) { }

void Tile::draw(sf::RenderWindow &w) {
    spr.setPosition(pos);
    w.draw(spr);
}

