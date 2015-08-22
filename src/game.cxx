#include <SFML/Graphics.hpp>

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "game.hxx"
#include "bullet.hxx"

Game::Game(sf::RenderWindow &w) : State(w), world(w) {
    txt = create_txt("consola.ttf", 14);
    base_gui = create_sprite("base_gui.png");
    health_bar = create_sprite("health.png");
    health_bar.setPosition(332, 18);
    init_bounds();
}

void Game::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            //L_("Key: %d\n", e.key.code);
            break;
        default: break;
    }
    world.handle_input(e);
}

void Game::update(const sf::Time &dt) {
    world.update(dt);

    // Lawl
    // TODO fix
    // Update hero handling!
    shared_ptr<Hero> hero = world.heroes[0];
    hero->move_stop();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) hero->move_left();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) hero->move_right();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) hero->move_up();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) hero->move_down();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) hero->fire();
}

void Game::draw() {
    world.draw();
    window.draw(base_gui);
    window.draw(health_bar);
}

void Game::set_monster_health(float frac) {
    // How to set % of health ;)
    health_bar.setScale(frac, 1);
}

