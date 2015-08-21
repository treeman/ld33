#include <memory>
using namespace std;

#include "die.hxx"
#include "butler.hxx"

map<string, shared_ptr<sf::Font>> fnts;
map<string, shared_ptr<sf::Texture>> texs;
map<string, shared_ptr<sf::SoundBuffer>> soundbuffers;

shared_ptr<sf::Font> get_font(string path) {
    auto it = fnts.find(path);
    if (it != fnts.end()) return it->second;

    shared_ptr<sf::Font> fnt(new sf::Font);
    string realpath = "fnt/" + path;
    if (!fnt->loadFromFile(realpath)) {
        die("Error! Couldn't load font: %s\n", realpath);
    }
    fnts.insert(make_pair(path, fnt));
    return fnt;
}

shared_ptr<sf::Texture> get_sprite(string path) {
    auto it = texs.find(path);
    if (it != texs.end()) return it->second;

    shared_ptr<sf::Texture> tex(new sf::Texture);
    string realpath = "gfx/" + path;
    if (!tex->loadFromFile(realpath)) {
        die("Error! Couldn't load texture: %s\n", realpath);
    }
    texs.insert(make_pair(path, tex));
    return tex;
}

shared_ptr<sf::SoundBuffer> get_soundbuffer(string path) {
    auto it = soundbuffers.find(path);
    if (it != soundbuffers.end()) return it->second;

    shared_ptr<sf::SoundBuffer> buffer(new sf::SoundBuffer);
    string realpath = "snd/" + path;
    if (!buffer->loadFromFile(realpath)) {
        die("Error! Couldn't load soundbuffer: %s\n", realpath);
    }
    soundbuffers.insert(make_pair(path, buffer));
    return buffer;
}

sf::Text create_txt(string path, int size, string txt) {
    sf::Text res(txt, *get_font(path), size);
    return res;
}

sf::Sprite create_sprite(string path) {
    auto tex = get_sprite(path);
    if (!tex) return sf::Sprite();
    return sf::Sprite(*tex);
}

sf::Sound create_sound(string path) {
    auto buffer = get_soundbuffer(path);
    if (!buffer) return sf::Sound();
    return sf::Sound(*buffer);
}

