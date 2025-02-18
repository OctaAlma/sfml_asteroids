#include "Asteroid.hpp"
#include <random>

Asteroid::Asteroid(){}

Asteroid::Asteroid(sf::Texture& asTex){
    asteroidSprite.setTexture(asTex);
    asteroidSprite.setOrigin(220.5f, 190.5f);

    asteroidSprite.setPosition(getRandom(MIN_ASTEROID_X, MAX_ASTEROID_X), getRandom(MIN_ASTEROID_Y, MAX_ASTEROID_Y));
    asteroidSprite.rotate(getRandom(0.0f, 360.0f));

    float sc = getRandom(MIN_ASTEROID_SIZE, MAX_ASTEROID_SIZE);
    asteroidSprite.scale(sc, sc);

    speed = getRandom(MIN_ASTEROID_SPEED, MAX_ASTEROID_SPEED);
    size = getRandom(MIN_ASTEROID_SIZE, MAX_ASTEROID_SIZE);

    dir.x = getRandom(-1.0f, 1.0f);
    dir.y = getRandom(-1.0f, 1.0f);
    normalize(dir);
}

void Asteroid::update(sf::Time delta){
    asteroidSprite.move(dir * speed * delta.asSeconds());
    sf::Vector2f pos = asteroidSprite.getPosition();
    snapPosition(pos);
    asteroidSprite.setPosition(pos);
}

sf::Sprite& Asteroid::getSprite(){
    return asteroidSprite; 
}
