#include "AsteroidBelt.hpp"
#include <string>
#include <iostream>
#include <algorithm>
#include <stack>
using std::cout, std::endl, std::vector;

AsteroidBelt::AsteroidBelt():textures(NUM_ASTEROID_TEXTURES), asteroids(NUM_STARTING_ASTEROIDS){
    std::string path = "./resources/asteroidX.png";
    int xInd = 20;

    for (unsigned int i = 0; i < NUM_ASTEROID_TEXTURES; i++){
        path[xInd] = (i + '0');

        if (!textures[i].loadFromFile(path)){
            cout << "Could not load texture file at " << path << endl;
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

// Creates new child asteroid if ast is big enough. 
// Child asteroids are pushed to the asteroids vector
void splitAsteroid(vector<Asteroid>& asteroids, Asteroid& ast){
    float newSize = ast.getSize() / 2.0f;
    if (newSize >= MIN_ASTEROID_SIZE){
        asteroids.push_back(Asteroid(ast, ChildDirection::PLUS_45));
        asteroids.push_back(Asteroid(ast, ChildDirection::MINUS_45));
    }
}

// swaps asteroid to the back of the list and removes it from the vector
void removeAsteroid(vector<Asteroid>& asteroids, int removeMe){
    if (asteroids.empty()) { return; }
    if (removeMe != asteroids.size()-1) {
        std::swap(asteroids[removeMe], asteroids[asteroids.size()-1]);
    }
    asteroids.pop_back();
}

bool AsteroidBelt::collided(Laser& l){
    sf::FloatRect laserBound = l.getSprite().getGlobalBounds();

    for (int i = 0; i < asteroids.size(); i++){
        if (asteroids[i].getSprite().getGlobalBounds().intersects(laserBound)){
            // we have an intersection...
            // remove the asteroid from the vector
            splitAsteroid(asteroids, asteroids[i]);
            removeAsteroid(asteroids, i);
            return true;
        }
    }
    
    return false;
}

std::vector<Asteroid>& AsteroidBelt::getAsteroids(){ return this->asteroids; }