#include "engine/butler.hxx"
#include "statusbar.hxx"

Statusbar::Statusbar(string s, FPoint pos) {
    txt = create_txt("consola.ttf", 14, s);
    txt.setPosition(pos);
    txt.setColor(sf::Color(0x362E0EFF));
}

void Statusbar::update(const sf::Time &dt) {
}

void Statusbar::draw(sf::RenderWindow &w) {
    w.draw(txt);
}

