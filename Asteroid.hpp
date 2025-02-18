#include <SFML/Graphics.hpp>
#include "./Definitions.h"

#define NUM_STARTING_ASTEROIDS 10

#define MIN_ASTEROID_SPEED 25.0f
#define MAX_ASTEROID_SPEED 75.0f

#define MIN_ASTEROID_SIZE 0.05f
#define MAX_ASTEROID_SIZE 0.25f

#define MIN_ASTEROID_X 0.0f
#define MAX_ASTEROID_X RESOLUTION_WIDTH

#define MIN_ASTEROID_Y 0.0f
#define MAX_ASTEROID_Y RESOLUTION_HEIGHT

class Asteroid{
private:
    sf::Sprite asteroidSprite;
    sf::Vector2f dir;
    float speed;
    float size;

public:
    Asteroid();
    Asteroid(sf::Texture& asTex);
    void update(sf::Time delta);
    sf::Sprite& getSprite();
};