#include <SFML/Graphics.hpp>
#include "./Definitions.h"

#define LASER_SPEED     10.0f

class Laser{
private:
    sf::Sprite laserSprite;
    sf::Vector2f dir;
    bool active;

public:
    Laser();
    void reset(sf::Vector2f pos, sf::Vector2f dir, sf::Texture& laserTex);
    void update(sf::Time delta);
    sf::Sprite& getSprite();
    bool isActive();
};