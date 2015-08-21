#include <memory>
using namespace std;

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Engine {
public:
    Engine();
    ~Engine() noexcept;

    void run();
private:
    unique_ptr<sf::RenderWindow> window;

    sf::Text fps_txt;
    int fps_frame_count;
    float fps;
    sf::Clock fps_timer;
};

