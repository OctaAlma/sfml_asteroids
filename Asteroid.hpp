#include <SFML/Graphics.hpp>
#include "./Definitions.h"

#define MIN_ASTEROID_SPEED      25.0f
#define MAX_ASTEROID_SPEED      75.0f

#define MIN_ASTEROID_SIZE       0.08f
#define MAX_ASTEROID_SIZE       0.3f

#define MIN_ASTEROID_X          0.0f
#define MAX_ASTEROID_X          RESOLUTION_WIDTH

#define MIN_ASTEROID_Y          0.0f
#define MAX_ASTEROID_Y          RESOLUTION_HEIGHT

const sf::Uint8 asteroid_colors[6][3] = 
{
    {255, 255, 255},    // White
    {215, 0, 21},       // red
    {48, 209, 88},      // green
    {10, 132, 255},     // blue
    {255, 159, 0},      // Orange
    {191, 90, 242}      // Purple
};

#define NUM_ASTEROID_COLORS     sizeof(asteroid_colors)

class Asteroid{
private:
    sf::Sprite asteroidSprite;
    sf::Vector2f dir;
    float speed;
    float size;

public:
    Asteroid();
    Asteroid(sf::Texture& asTex, unsigned int colorInd=0);
    void update(sf::Time delta);
    sf::Sprite& getSprite();
};