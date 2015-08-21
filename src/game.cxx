#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "game.hxx"

Game::Game(sf::RenderWindow &w) : State(w) {
    txt = create_txt("consola.ttf", 14);
    spr = create_sprite("tst.png");
    spr.setPosition(FPoint(200, 400));
}

void Game::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            printf("Key: %d\n", e.key.code);
            fflush(stdout);
            break;
        default: break;
    }
}

void Game::update(const sf::Time &dt) {
}

void Game::draw() {
    window.draw(spr);
}

