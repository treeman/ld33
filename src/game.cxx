#include <SFML/Graphics.hpp>

#include "engine/butler.hxx"
#include "engine/pos.hxx"
#include "engine/locator.hxx"
#include "game.hxx"
#include "bullet.hxx"

Game::Game(sf::RenderWindow &w) : State(w), world(w) {
    L_("Building Game\n");
    txt = create_txt("consola.ttf", 14);
    //base_gui = create_sprite("base_gui.png");
    health_gui = create_sprite("health_gui.png");
    health_bar = create_sprite("health.png");
    health_gui.setPosition(332, 18);
    health_bar.setPosition(332, 18);

    h = create_sprite("h.png");
    hf = create_sprite("hf.png");
    j = create_sprite("j.png");
    jf = create_sprite("jf.png");
    k = create_sprite("k.png");
    kf = create_sprite("kf.png");
    l = create_sprite("l.png");
    lf = create_sprite("lf.png");

    h.setPosition(20, 535); hf.setPosition(20, 535);
    j.setPosition(64, 535); jf.setPosition(64, 535);
    k.setPosition(105, 535); kf.setPosition(105, 535);
    l.setPosition(150, 535); lf.setPosition(150, 535);

    init_bounds();
    for (auto h : world.heroes) {
        ais.push_back(shared_ptr<AI>(new AI(h, world)));
    }
}

void Game::handle_input(const sf::Event &e) {
    switch (e.type) {
        case sf::Event::KeyPressed:
            //L_("Key: %d\n", e.key.code);
            break;
        default: break;
    }
    world.handle_input(e);
}

void Game::update(const sf::Time &dt) {
    world.update(dt);
    for (auto ai : ais) ai->update(dt);
    ais.erase(remove_if(ais.begin(),
                        ais.end(),
                        [](shared_ptr<AI> x) { return x->hero->is_dead; }),
                 ais.end());

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

    //const float x = 35;
    //const float y = 535;
    window.draw(hf);
    window.draw(h);
    window.draw(jf);
    window.draw(j);
    window.draw(kf);
    window.draw(k);
    window.draw(lf);
    window.draw(l);
}

void Game::update_monster_health() {
    float frac = world.monster->monster_life / world.monster->max_monster_life;
    //D_.tmp(fmt("Health: %f", frac));

    // How to set % of health ;)
    health_bar.setScale(frac, 1);
}

