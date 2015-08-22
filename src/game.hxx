#pragma once

#include "engine/state.hxx"
#include "world.hxx"
#include "statusbar.hxx"

class Game : public State {
public:
    Game(sf::RenderWindow &w);

    string id() const override { return "game"; }

    void handle_input(const sf::Event &e) override;
    void update(const sf::Time &dt) override;
    void draw() override;
private:
    sf::Text txt;
    World world;
    sf::RectangleShape gui_back;
    vector<Statusbar> bars;
};

