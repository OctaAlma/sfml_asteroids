#include "./Game.hpp"
#include "./Definitions.h"
#include <iostream>
#include <math.h>
using std::cout, std::endl, std::vector;

Game::Game():window(sf::VideoMode(RESOLUTION_WIDTH, RESOLUTION_HEIGHT), "SFML App"), player(), belt(){}

void Game::run(){
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(window.isOpen()){
        // Clock.restart() returns the time elapsed since the clock was last restarted
        processEvents();

        timeSinceLastUpdate += clock.restart();
        while(timeSinceLastUpdate > secondsPerFrame){
            timeSinceLastUpdate -= secondsPerFrame;
            update(secondsPerFrame);
            render();
        }
    }
}

void Game::handleInputs(sf::Keyboard::Key key, bool pressed){
    player.updateMovement(key, pressed);
}

// Handles user inputs.
// Polls the paplication window for any input events.
// will close the window if a Closed event occurs
void Game::processEvents(){
    sf::Event event;
    while(window.pollEvent(event)){
        switch (event.type)
        {
            case (sf::Event::KeyPressed):
                handleInputs(event.key.code, true);
                break;

            case (sf::Event::KeyReleased):
                handleInputs(event.key.code, false);
                break;

            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
        }

    }
}

void collisionDetection(Player& p, AsteroidBelt& ab){
    vector<Asteroid>& asteroids = ab.getAsteroids();
    vector<Laser>& lasers = p.getLasers();

    for (auto& l : lasers){

        if (!l.isActive()){ continue; }

        if (ab.collided(l)){
            l.setInactive(); // GOTTA UPDATE PLAYER TOO!!!
            p.decreaseActiveLasers();
        }
    }
}

void Game::update(sf::Time delta){
    player.update(delta);
    belt.update(delta);
    collisionDetection(player, belt);
}

void Game::render(){
    window.clear();
    window.draw(player.getSprite(), sf::RenderStates::Default);
    belt.draw(window);
    player.drawLasers(window);
    window.display();
}