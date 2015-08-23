#include "shapedebug.hxx"
#include "locator.hxx"

const sf::Color lcol = sf::Color(0x39C5CCFF);

ShapeDebug::ShapeDebug() { }

void ShapeDebug::line(FPoint p1, FPoint p2) {
    lines.push_back(make_pair(p1, p2));
}
void ShapeDebug::add(shared_ptr<sf::Shape> s) {
    shapes.push_back(s);
}
void ShapeDebug::draw(sf::RenderWindow &w) {
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

