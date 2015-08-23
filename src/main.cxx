#include <ctime>

#include "engine/engine.hxx"
#include "engine/locator.hxx"
#include "game.hxx"
#include "instr.hxx"

int main()
{
    shared_ptr<Engine> engine(new Engine());
    StateStack &states = Locator::get_statestack();
    states.push(shared_ptr<State>(new Instr(Locator::get_window())));
    engine->run();
    return 0;
}

