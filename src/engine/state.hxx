#pragma once

#include <string>
using namespace std;

// Base class of each state in the game
// subclass and feed to engine. For easy switching!
class State {
public:
    State(sf::RenderWindow &w) : window(w) { }
    virtual ~State() {};

    virtual string id() const = 0;

    virtual void handle_input(const sf::Event &e) { }
    virtual void update(const sf::Time &dt) { }
    virtual void draw() { }
protected:
    sf::RenderWindow &window;
};

