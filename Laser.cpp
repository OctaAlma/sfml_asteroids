#include "./Laser.hpp"

Laser::Laser(){}

void Laser::reset(sf::Vector2f pos, sf::Vector2f direction, sf::Texture& laserTex){
    laserSprite.setTexture(laserTex);
    sf::FloatRect bounds = laserSprite.getLocalBounds();
    laserSprite.setOrigin(bounds.width/2.0f, bounds.height/2.0f);

    laserSprite.setPosition(pos);
    dir = direction;
    
    active = true;
}

void Laser::update(sf::Time delta){
    sf::Vector2f pos = laserSprite.getPosition();
    if (!inMap(pos)){ 
        active = false;
        return;
    }

    laserSprite.move(dir * LASER_SPEED * delta.asSeconds());
}

sf::Sprite& Laser::getSprite(){ return this->laserSprite; }

bool Laser::isActive(){ return this->active; }