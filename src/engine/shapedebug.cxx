#include "shapedebug.hxx"
#include "locator.hxx"

const sf::Color lcol = sf::Color(0x39C5CCFF);
const sf::Color scol = sf::Color(0xED95B622);

ShapeDebug::ShapeDebug() { }

void ShapeDebug::line(FPoint p1, FPoint p2) {
    lines.push_back(make_pair(p1, p2));
}
void ShapeDebug::add(shared_ptr<sf::Shape> s) {
    s->setOutlineColor(lcol);
    s->setOutlineThickness(1.0);
    s->setFillColor(sf::Color(0x00000000));
    shapes.push_back(s);
}
void ShapeDebug::draw(sf::RenderWindow &w) {
    for (auto s : shapes) w.draw(*s);

    // Slow? Meh.
    for (auto l : lines) {
        sf::Vertex line[] = { sf::Vertex(l.first, lcol), sf::Vertex(l.second, lcol) };
        w.draw(line, 2, sf::Lines);
    }
}
void ShapeDebug::tick() {
    shapes.clear();
    lines.clear();
}

