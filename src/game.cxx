#include <SFML/Graphics.hpp>

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "game.hxx"

Game::Game(sf::RenderWindow &w) : State(w), world(w) {
    txt = create_txt("consola.ttf", 14);

    // Gui
    const int gui_height = 140;
    gui_back.setSize(FPoint(800, gui_height));
    gui_back.setPosition(0, 600 - gui_height);
    gui_back.setFillColor(sf::Color(0xFFF1BAFF));

    const int left_x = 380;
    const int right_x = 550;
    const int top_y = 475;
    const int txt_h = 25;

    vector<string> left = { "BRAINZ", "Comfort", "Bladder", "Energy" };
    for (size_t i = 0; i < left.size(); ++i) {
        bars.push_back(Statusbar(left[i], FPoint(left_x, top_y + i * txt_h)));
    }

    vector<string> right = { "Fun", "Social", "Hygiene", "Environment" };
    for (size_t i = 0; i < right.size(); ++i) {
        bars.push_back(Statusbar(right[i], FPoint(right_x, top_y + i * txt_h)));
    }
}

void Game::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            //L_("Key: %d\n", e.key.code);
            break;
        default: break;
    }
}

void Game::update(const sf::Time &dt) {
    world.update(dt);
}

void Game::draw() {
    world.draw();

    // Draw gui
    window.draw(gui_back);
    for (auto x = bars.begin(); x != bars.end(); ++x) {
        x->draw(window);
    }
}

