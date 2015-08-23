#pragma once

#include "engine/state.hxx"
#include "world.hxx"
#include "statusbar.hxx"
#include "ai.hxx"

class Instr : public State {
public:
    Instr(sf::RenderWindow &w);

    string id() const override { return "instr"; }

    void handle_input(const sf::Event &e) override;
    void update(const sf::Time &dt) override;
    void draw() override;

    sf::Sprite instr;
    void go();
};

