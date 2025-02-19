#include "./Asteroid.hpp"
#include <vector>

#define NUM_ASTEROID_TEXTURES   4
#define NUM_STARTING_ASTEROIDS  15

class AsteroidBelt{
private:
    std::vector<sf::Texture> textures;
    std::vector<Asteroid> asteroids;
public:
    AsteroidBelt();
    void update(sf::Time delta);
    void draw(sf::RenderWindow& window);
};