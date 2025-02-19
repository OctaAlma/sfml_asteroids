#include "AsteroidBelt.hpp"
#include <string>
#include <iostream>

AsteroidBelt::AsteroidBelt():textures(NUM_ASTEROID_TEXTURES), asteroids(NUM_STARTING_ASTEROIDS){
    std::string path = "./resources/asteroidX.png";
    int xInd = 20;

    for (unsigned int i = 0; i < NUM_ASTEROID_TEXTURES; i++){
        path[xInd] = (i + '0');

        if (!textures[i].loadFromFile(path)){
            std::cout << "Could not load texture file at " << path << std::endl;
            exit(1);
        }
    }

    for (unsigned int i = 0; i < NUM_STARTING_ASTEROIDS; i++){
        asteroids[i] = Asteroid(textures[i%NUM_ASTEROID_TEXTURES], i%NUM_ASTEROID_COLORS);
    }
}

void AsteroidBelt::update(sf::Time delta){
    for (auto& ast : asteroids){
        ast.update(delta);
    }
}

void AsteroidBelt::draw(sf::RenderWindow& window){
    for (auto& ast : asteroids){
        window.draw(ast.getSprite(), sf::RenderStates::Default);
    }
}