#include <ctime>

#include "engine/engine.hxx"
#include "engine/locator.hxx"
#include "game.hxx"

int main()
{
    shared_ptr<Engine> engine(new Engine());
    StateStack &states = Locator::get_statestack();
    states.add_generator("game", []{ return new Game(Locator::get_window()); });
    states.push_generated("game");
    engine->run();
    return 0;
}

