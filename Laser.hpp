#pragma once
#ifndef LASER_HPP
#define LASER_HPP

#include <SFML/Graphics.hpp>
#include "./Definitions.h"

#define LASER_SPEED         900.0f
#define LASER_ROT_SPEED     500.0f
#define LASER_SCALE         0.1f
#define LASER_COOLDOWN      0.2f // the time, in seconds, before the player can shoot another laser


class Laser{
private:
    sf::Sprite laserSprite;
    sf::Vector2f dir;
    bool active;

public:
    Laser();
    Laser(sf::Texture& laserTex);
    void reset(sf::Vector2f pos, sf::Vector2f dir);
    void update(sf::Time delta);
    sf::Sprite& getSprite();
    bool isActive();
    void setInactive();
};

#endif