#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "world.hxx"

const int tile_width = 32;
const int x_tiles = 20;
const int y_tiles = 15;

World::World(sf::RenderWindow &w) : window(w), tiles(x_tiles, vector<Tile>(y_tiles)) {
    spr = create_sprite("tst.png");
    spr.setPosition(FPoint(200, 200));

    for (size_t x = 0; x < x_tiles; ++x) {
        for (size_t y = 0; y < y_tiles; ++y) {
            tiles[x][y].pos = FPoint(0 + tile_width * x, 0 + tile_width * y);
        }
    }
}

void World::update(const sf::Time &dt) {
}

void World::draw() {
    window.draw(spr);

    //for (auto it = begin(tiles); it != end(tiles); ++it) {
        //for (auto x = it->begin(); x != it->end(); ++x) {
            //x->draw(window);
        //}
    //}
}

// BRAINZ           Fun
// Comfort          Social
// Bladder          Hygiene
// Energy           Environment

// Wants/Fears?

