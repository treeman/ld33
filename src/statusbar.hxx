#pragma once

#include <SFML/Graphics.hpp>
#include <string>
using namespace std;

#include "engine/pos.hxx"

class Statusbar {
public:
    Statusbar(string txt, FPoint pos);

    void update(const sf::Time &dt);
    void draw(sf::RenderWindow &w);
private:
    sf::Text txt;
    sf::RectangleShape bar;
};

