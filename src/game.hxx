#pragma once

#include "engine/state.hxx"
#include "world.hxx"
#include "statusbar.hxx"
#include "ai.hxx"

class Game : public State {
public:
    Game(sf::RenderWindow &w, int heroes);

    string id() const override { return "game"; }

    void handle_input(const sf::Event &e) override;
    void update(const sf::Time &dt) override;
    void draw() override;

    sf::Text txt;
    World world;
    sf::Sprite health_gui;
    sf::Sprite health_bar;

    void update_monster_health();

    vector<shared_ptr<AI>> ais;
    sf::Sprite victory;
    sf::Clock victory_clock;
    bool has_victory;
    void next_game();
    int heroes;

    bool is_game_over;
    sf::Sprite game_over;
    sf::Clock game_over_clock;
    void restart();

    sf::Sound vic_snd;
};

