#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace std;

// Lazy resource loading be here
shared_ptr<sf::Font> get_font(string path);
shared_ptr<sf::Texture> get_texture(string path);

sf::Text create_txt(string path, int size, string txt = "");
sf::Sprite create_sprite(string path);
