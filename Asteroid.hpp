#include <SFML/Graphics.hpp>
#include "./Definitions.h"

#define MIN_ASTEROID_SPEED      25.0f
#define MAX_ASTEROID_SPEED      75.0f

#define MIN_ASTEROID_SIZE       0.1f
#define MAX_ASTEROID_SIZE       0.5f

#define MIN_ASTEROID_X          0.0f
#define MAX_ASTEROID_X          RESOLUTION_WIDTH

#define MIN_ASTEROID_Y          0.0f
#define MAX_ASTEROID_Y          RESOLUTION_HEIGHT

enum ChildDirection{
    SAME_DIR,
    PLUS_90,
    MINUS_90
};

const sf::Uint8 asteroid_colors[9][3] = 
{
    {255, 255, 255},    // white
    {215, 0, 21},       // red
    {48, 209, 88},      // green
    {10, 132, 255},     // blue
    {255, 159, 0},      // orange
    {0, 255, 255},      // cyan
    {255, 51, 255},     // magenta
    {255, 255, 0},      // yellow
    {178, 100, 50}      // brown
};

#define NUM_ASTEROID_COLORS         (sizeof(asteroid_colors)/3)

class Asteroid{
private:
    sf::Sprite asteroidSprite;
    sf::Vector2f dir;
    float speed;
    float size;

public:
    Asteroid();
    Asteroid(sf::Texture& asTex, unsigned int colorInd=0);
    Asteroid(Asteroid& father, ChildDirection newDir);
    void update(sf::Time delta);
    sf::Sprite& getSprite();
    float getSize();
};