#include <cstdlib>
#include <ctime>

#include "engine.hxx"
#include "locator.hxx"
#include "rand.hxx"
#include "butler.hxx"
#include "printlogger.hxx"
#include "visualdebug.hxx"

Engine::Engine() {
    // Log to console atm
    Locator::provide_logger(unique_ptr<Logger>(new Printlogger()));
    L_("Logger is armed.\n");

    window.reset(new sf::RenderWindow(sf::VideoMode(800, 600), "ld33", sf::Style::None));

    Locator::provide_window(window.get());
    L_("Window opened.\n");

    Locator::provide_debug(unique_ptr<VisualDebug>(new VisualDebug({10, 30})));
    Locator::provide_statestack(unique_ptr<StateStack>(new StateStack()));

    set_seed(time(0));

    fps_txt = create_txt("lucon.ttf", 20);
    fps_txt.setPosition(5, 3);

    fps_frame_count = 0;
    fps = 0;
}

Engine::~Engine() noexcept {
    L_("Destructing Engine.\n");
}

void Engine::run() {
    L_("Starting game loop!\n");

    StateStack &state_handler = Locator::get_statestack();
    sf::Clock clock;

    while (window->isOpen() && state_handler.has_current()) {
        shared_ptr<State> state = state_handler.current();
        sf::Event e;
        while (window->pollEvent(e)) {
            switch (e.type) {
                case sf::Event::Closed:
                    L_("closing...\n");
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    //if (e.key.code == sf::Keyboard::H) {
                        //if (state->id() != "help")
                            //push_next_state("help", window);
                    //}
                    if (e.key.code == sf::Keyboard::Escape) {
                        L_("exiting...\n");
                        window->close();
                    }
                    break;
                default: break;
            }
            state->handle_input(e);

            sf::Time dt = clock.restart();

            // Simply update each second,
            // no need for anything more sophisticated.
            ++fps_frame_count;
            const float fps_time = fps_timer.getElapsedTime().asSeconds();
            if (fps_time >= 1.0) {
                fps = fps_frame_count / fps_time;
                fps_frame_count = 0;
                fps_timer.restart();
            }

            // Debug mouse position
            auto mp = sf::Mouse::getPosition(*window);
            D_.set_key("mpos", to_string(mp.x) + ", " + to_string(mp.y));

            // Update shit
            state->update(dt);

            // Draw things!
            window->clear();
            state->draw();

            // Debugger logs and possibly draws last.
            Locator::get_debug().update();

            fps_txt.setString(to_string((int)fps));
            window->draw(fps_txt);

            window->display();
        }
    }
}

