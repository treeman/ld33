#include <ctime>

#include "engine/engine.hxx"
#include "engine/locator.hxx"
#include "game.hxx"

int main()
{
    shared_ptr<Engine> engine(new Engine());
    StateStack &states = Locator::get_statestack();
    states.push(shared_ptr<State>(new Game(Locator::get_window(), 1)));
    //states.add_generator("game", []{ return new Game(Locator::get_window(), 1); });
    //states.push_generated("game");
    engine->run();
    return 0;
}

