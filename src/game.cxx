#include <SFML/Graphics.hpp>

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "game.hxx"
#include "bullet.hxx"

Game::Game(sf::RenderWindow &w, int _heroes) : State(w), world(w, _heroes), heroes(_heroes) {
    L_("Building Game\n");
    txt = create_txt("consola.ttf", 14);
    //base_gui = create_sprite("base_gui.png");
    health_gui = create_sprite("health_gui.png");
    health_bar = create_sprite("health.png");
    health_gui.setPosition(432, 18);
    health_bar.setPosition(432, 18);

    init_bounds();
    for (auto h : world.heroes) {
        ais.push_back(shared_ptr<AI>(new AI(h, world)));
    }

    victory = create_sprite("victoryscreen.png");
    has_victory = false;
    game_over = create_sprite("gameover.png");
    is_game_over = false;

    vic_snd = create_sound("Pickup_Coin11.wav");
}

void Game::handle_input(const sf::Event &e) {
    //switch (e.type) {
        //case sf::Event::KeyPressed:
            ////L_("Key: %d\n", e.key.code);
            //break;
        //default: break;
    //}
    world.handle_input(e);
}

void Game::update(const sf::Time &dt) {
    if (has_victory) return;
    if (is_game_over) return;

    world.update(dt);
    for (auto ai : ais) ai->update(dt);
    ais.erase(remove_if(ais.begin(),
                        ais.end(),
                        [](shared_ptr<AI> x) { return x->hero->is_dead; }),
                 ais.end());
    if (ais.empty() && !has_victory) {
        vic_snd.play();
        victory_clock.restart();
        has_victory = true;
    }
    if (world.monster->is_dead) {
        game_over_clock.restart();
        is_game_over = true;
    }

    // Lawl
    // TODO fix
    // Update hero handling!
    //shared_ptr<Hero> hero = world.heroes[0];
    //hero->move_stop();
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) hero->move_left();
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) hero->move_right();
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) hero->move_up();
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) hero->move_down();
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::RControl)) hero->fire();

    update_monster_health();
}

void Game::draw() {
    world.draw();
    //window.draw(base_gui);
    window.draw(health_bar);
    window.draw(health_gui);

    if (has_victory) {
        window.draw(victory);
        if (victory_clock.getElapsedTime().asSeconds() > 2) {
            next_game();
        }
    }

    if (is_game_over) {
        window.draw(game_over);
        if (game_over_clock.getElapsedTime().asSeconds() > 2) {
            restart();
        }
    }
}

void Game::update_monster_health() {
    float frac = world.monster->monster_life / world.monster->max_monster_life;
    //D_.tmp(fmt("Health: %f", frac));

    // How to set % of health ;)
    health_bar.setScale(frac, 1);
}

// Yeah I'm doing it. What are you gonna do about it??
void Game::next_game() {
    StateStack &states = Locator::get_statestack();
    shared_ptr<Game> next(new Game(Locator::get_window(), heroes + 1));
    next->world.monster->set_pos(world.monster->pos);
    states.pop();
    states.push(next);
}

void Game::restart() {
    StateStack &states = Locator::get_statestack();
    shared_ptr<Game> next(new Game(Locator::get_window(), heroes));
    next->world.monster->set_pos(world.monster->pos);
    states.pop();
    states.push(next);
}

