#include <SFML/Graphics.hpp>

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "game.hxx"
#include "instr.hxx"
#include "bullet.hxx"

Instr::Instr(sf::RenderWindow &w) : State(w) {
    L_("Building instr\n");
    instr = create_sprite("instr.png");
}

void Instr::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed: go();
        default: break;
    }
}
void Instr::update(const sf::Time &dt) { }
void Instr::draw() {
    window.clear(sf::Color::White);
    window.draw(instr);
}

void Instr::go() {
    StateStack &states = Locator::get_statestack();
    states.push(shared_ptr<State>(new Game(Locator::get_window(), 1)));
}

