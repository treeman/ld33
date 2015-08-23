#pragma once

#include "engine/state.hxx"
#include "world.hxx"
#include "statusbar.hxx"
#include "ai.hxx"

class Game : public State {
public:
    Game(sf::RenderWindow &w);

    string id() const override { return "game"; }

    void handle_input(const sf::Event &e) override;
    void update(const sf::Time &dt) override;
    void draw() override;

    sf::Text txt;
    World world;
    sf::Sprite health_gui;
    sf::Sprite health_bar;

    sf::Sprite h, hf, j, jf, k, kf, l, lf;

    void update_monster_health();

    vector<shared_ptr<AI>> ais;
};

