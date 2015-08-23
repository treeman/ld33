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
    sf::Sprite base_gui;
    sf::Sprite health_bar;

    void update_monster_health();

    vector<AI> ais;
};

// Weapons:
// 1. Eye lazer
// 2. Left whirler
// 3. Right whirler
// 4. Bouncer
// 5. Rockets

// Powerups:
// 1. Bullet masher :w

// Status:
// 1. Life

