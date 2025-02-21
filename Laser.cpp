#include "./Laser.hpp"

Laser::Laser(){
    active = false;
}

Laser::Laser(sf::Texture& tex){ 
    laserSprite.setTexture(tex);
    sf::FloatRect bounds = laserSprite.getLocalBounds();
    laserSprite.setOrigin(bounds.width / 2.0f, bounds.height / 2.0f);
    laserSprite.setScale(LASER_SCALE, LASER_SCALE);
    active = false;
}

void Laser::reset(sf::Vector2f pos, sf::Vector2f direction){
    laserSprite.setPosition(pos);
    dir = direction;
    active = true;
}

void Laser::update(sf::Time delta){
    if (active == false){ return; }

    sf::Vector2f pos = laserSprite.getPosition();
    laserSprite.move(dir * LASER_SPEED * delta.asSeconds());
    laserSprite.rotate(LASER_ROT_SPEED * delta.asSeconds());
    
    if (!inMap(pos)){ 
        active = false;
        return;
    }

}

sf::Sprite& Laser::getSprite(){ return this->laserSprite; }

bool Laser::isActive(){ return this->active; }

void Laser::setInactive() { this->active = false; }