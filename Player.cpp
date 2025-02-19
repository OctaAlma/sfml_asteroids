#include "Player.hpp"
#include "./Definitions.h"
#include <iostream>
#include <string.h>
#include <math.h>
using std::cout, std::endl;

Player::Player(){
    if (!playerTexture.loadFromFile("./resources/ship.png")){
        // handle loading error...
        cout << "Could not load sprite for ship...\n";
        exit(1);
    }

    memset(moving, 0, sizeof(bool)*4);
    memset(rotating, false, sizeof(bool)*2);
    this->rotation = 0;

    this->playerSprite.setTexture(playerTexture);
    sf::FloatRect bounds = playerSprite.getLocalBounds();
    this->playerSprite.setOrigin({bounds.width / 2.0f, bounds.height / 2.0f});
    this->playerSprite.setPosition(PLAYER_ORIGIN_X, PLAYER_ORIGIN_Y);
    this->playerSprite.setScale(SHIP_SCALE, SHIP_SCALE);
}

sf::Sprite& Player::getSprite(){ return this->playerSprite; }

void Player::update(sf::Time delta){

    applyPhysics(rotating[RIGHT], rotating[LEFT], angularSpeed, ANGULAR_INCREASE, 
        NATURAL_ANGULAR_DEC, MAX_ANGULAR_SPEED, ANGULAR_THRESHOLD);

    // Horizontal direction processing
    applyPhysics(moving[UP], moving[DOWN], momentumVec.y, SPEED_INCREASE, 
        NATURAL_SPEED_DEC, MAX_SPEED, SPEED_THRESHOLD);

    applyPhysics(moving[RIGHT], moving[LEFT], momentumVec.x, SPEED_INCREASE, 
        NATURAL_SPEED_DEC, MAX_SPEED, SPEED_THRESHOLD);

    // rotate the momentum vector based on the orientation of the ship
    sf::Vector2f rotMomentumVec = momentumVec;
    rotateVec(rotMomentumVec, playerSprite.getRotation());

    playerSprite.move(rotMomentumVec * delta.asSeconds());
    playerSprite.rotate(angularSpeed * delta.asSeconds());

    sf::Vector2f pos = playerSprite.getPosition();
    snapPosition(pos);
    playerSprite.setPosition(pos);
}

void Player::updateMovement(sf::Keyboard::Key key, bool pressed){
    if (key == sf::Keyboard::W){
        moving[UP] = pressed;
    }
    // else if (key == sf::Keyboard::A){
    //     moving[LEFT] = pressed;
    // }
    else if (key == sf::Keyboard::S){
        moving[DOWN] = pressed;
    }
    // else if (key == sf::Keyboard::D){
    //     moving[RIGHT] = pressed;
    // }
    else if (key == sf::Keyboard::Comma){
        rotating[LEFT] = pressed;
    }
    else if (key == sf::Keyboard::Period){
        rotating[RIGHT] = pressed;
    }
    else if (key == sf::Keyboard::R){
        playerSprite.setPosition(100.0f, 100.0f);
    }
}

sf::Vector2f Player::getPos(){
    return playerSprite.getPosition();
}

sf::Vector2f Player::getDir(){
    sf::Vector2f v01(0.0, 1.0);
    rotateVec(v01, playerSprite.getRotation());
    return v01;
}