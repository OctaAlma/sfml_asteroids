#include <SFML/Graphics.hpp>
#include "Player.hpp"

const sf::Time secondsPerFrame = sf::seconds(1.0f / 120.0f);

class Game{
public:
    Game();
    void run();

private:
    void handleInputs(sf::Keyboard::Key, bool pressed);
    void processEvents();
    void update(sf::Time delta);
    void render();

    sf::RenderWindow window;
    Player player;
};