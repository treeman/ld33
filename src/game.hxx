#pragma once

#include "engine/state.hxx"

class Game : public State {
public:
    Game(sf::RenderWindow &w);

    string id() const override { return "game"; }

    void handle_input(const sf::Event &e) override;
    void update(const sf::Time &dt) override;
    void draw() override;
private:
    sf::Text txt;
    sf::Sprite spr;
    sf::Sound snd;
};

