#include "Asteroid.hpp"
#include <random>
#include <iostream>
using std::cout, std::endl;

Asteroid::Asteroid(){}

Asteroid::Asteroid(sf::Texture& asTex, unsigned int colorInd){
    asteroidSprite.setTexture(asTex);
    sf::FloatRect bounds = asteroidSprite.getLocalBounds();
    asteroidSprite.setOrigin(bounds.width/2.0f, bounds.height/2.0f);

    asteroidSprite.setPosition(getRandom(MIN_ASTEROID_X, MAX_ASTEROID_X), getRandom(MIN_ASTEROID_Y, MAX_ASTEROID_Y));
    asteroidSprite.rotate(getRandom(0.0f, 360.0f));

    size = getRandom(MIN_ASTEROID_SIZE, MAX_ASTEROID_SIZE);
    asteroidSprite.scale(size, size);

    speed = getRandom(MIN_ASTEROID_SPEED, MAX_ASTEROID_SPEED);

    dir.x = getRandom(-1.0f, 1.0f);
    dir.y = getRandom(-1.0f, 1.0f);
    normalize(dir);

    // set the color of the asteroid
    sf::Color c(asteroid_colors[colorInd][0], asteroid_colors[colorInd][1], asteroid_colors[colorInd][2]);
    asteroidSprite.setColor(c);
}

// Creates a child asteroid given a "father" asteroid and a direction shift
Asteroid::Asteroid(Asteroid& father, ChildDirection newDir){
    asteroidSprite = father.asteroidSprite;
    speed = std::min(father.speed * 1.25f, MAX_ASTEROID_SPEED);
    size = father.size / 2.0f;
    asteroidSprite.setScale(size, size);
    dir = father.dir;

    if (newDir == PLUS_90){
        rotateVec(dir, 90.0f);
    }
    else if (newDir == MINUS_90){
        rotateVec(dir, -90.0f);
    }
}

void Asteroid::update(sf::Time delta){
    asteroidSprite.move(dir * speed * delta.asSeconds());
    sf::Vector2f pos = asteroidSprite.getPosition();
    snapPosition(pos);
    asteroidSprite.setPosition(pos);
}

sf::Sprite& Asteroid::getSprite(){ return asteroidSprite; }
float Asteroid::getSize() { return size; }