#include "Player.hpp"
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

    this->playerSprite.setOrigin({592, 592});
    this->playerSprite.setTexture(playerTexture);
    this->playerSprite.setPosition(100.0f, 100.0f);
    this->playerSprite.setScale(0.1f, 0.1f);
}

sf::Sprite& Player::getSprite(){ return this->playerSprite; }

void applyPhysics(bool optInc, bool optDec, float& num, float increase, float naturalDecrease, float maxNum, float minNum){
    if (optDec ^ optInc){
        if (optDec){ num -= increase; }
        if (optInc){ num += increase; }
    }
    else{
        if (abs(num) < minNum){ num = 0.0f; }
        else if (num > 0.0f){ num -= naturalDecrease; }
        else if (num < 0.0f) { num += naturalDecrease; }
    }

    // Snap num to max if exceeding
    if (abs(num) > maxNum){
        if (num < 0.0f){ num = -maxNum; }
        else if (num > 0.0f){ num = maxNum; }
    }
}

sf::Vector2f rotateVec(sf::Vector2f vec, float angle){
    float sinTheta = std::sin(angle * M_PI / 180.0f);
    float cosTheta =  std::cos(angle * M_PI / 180.0f);
    
    sf::Vector2f res;
    res.x = vec.x * cosTheta + vec.y * sinTheta;
    res.y = vec.x * sinTheta - vec.y * cosTheta;

    return res;
}

void Player::update(sf::Time delta){

    applyPhysics(rotating[RIGHT], rotating[LEFT], angularSpeed, ANGULAR_INCREASE, 
        NATURAL_ANGULAR_DEC, MAX_ANGULAR_SPEED, ANGULAR_THRESHOLD);

    playerSprite.rotate(angularSpeed * delta.asSeconds());

    // Horizontal direction processing
    applyPhysics(moving[UP], moving[DOWN], momentumVec.y, SPEED_INCREASE, 
        NATURAL_SPEED_DEC, MAX_SPEED, SPEED_THRESHOLD);

    applyPhysics(moving[RIGHT], moving[LEFT], momentumVec.x, SPEED_INCREASE, 
        NATURAL_SPEED_DEC, MAX_SPEED, SPEED_THRESHOLD);

    // rotate the momentum vector based on the orientation of the ship
    sf::Vector2f rotMomentumVec = rotateVec(momentumVec, playerSprite.getRotation());

    playerSprite.move(rotMomentumVec * delta.asSeconds());
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
    else if (key == sf::Keyboard::A){
        rotating[LEFT] = pressed;
    }
    else if (key == sf::Keyboard::Comma){
        rotating[RIGHT] = pressed;
    }
    else if (key == sf::Keyboard::Period){
        playerSprite.setPosition(100.0f, 100.0f);
    }
}