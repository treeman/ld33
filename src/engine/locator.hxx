#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "debug.hxx"
#include "state.hxx"
#include "statestack.hxx"
#include "log.hxx"

// Static accessor class for global functions, singletons etc
// purely for convenience!
class Locator {
public:
    static Debug &get_debug();
    static void provide_debug(unique_ptr<Debug> debug);

    static bool has_window();
    static sf::RenderWindow &get_window();
    static void provide_window(sf::RenderWindow *window);

    static StateStack &get_statestack();
    static void provide_statestack(unique_ptr<StateStack> s);

    static Logger &get_logger();
    static void provide_logger(unique_ptr<Logger> logger);
private:
    static unique_ptr<Debug> debug;
    static sf::RenderWindow *window;
    static unique_ptr<StateStack> statestack;
    static unique_ptr<Logger> logger;
};

