#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
using namespace std;

#include "pos.hxx"

class ShapeDebug {
public:
    ShapeDebug();

    void line(FPoint p1, FPoint p2);
    void add(shared_ptr<sf::Shape> s);

    void draw(sf::RenderWindow &w);
    void tick();
private:
    vector<shared_ptr<sf::Shape>> shapes;
    vector<pair<FPoint, FPoint>> lines;
};

