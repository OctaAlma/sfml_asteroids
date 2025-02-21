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

    if (!laserTexture.loadFromFile("./resources/projectile.png")){
        // handle loading error...
        cout << "Could not load sprite for ship...\n";
        exit(1);
    }

    memset(moving, 0, sizeof(bool)*4);
    memset(rotating, false, sizeof(bool)*2);
    rotation = 0;

    playerSprite.setTexture(playerTexture);
    sf::FloatRect bounds = playerSprite.getLocalBounds();
    playerSprite.setOrigin({bounds.width / 2.0f, bounds.height / 2.0f});
    playerSprite.setPosition(PLAYER_ORIGIN_X, PLAYER_ORIGIN_Y);
    playerSprite.setScale(SHIP_SCALE, SHIP_SCALE);

    activeLasers = 0;
    lastShot.restart();
    lasers.reserve(MAX_LASER_SHOTS);
    for (int i = 0; i < MAX_LASER_SHOTS; i++){
        lasers.push_back(Laser(laserTexture));
    }
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

    // update the lasers
    for (auto& l : lasers){
        if (l.isActive()) { 
            l.update(delta); 
            
            if (!l.isActive() && activeLasers != 0){
                activeLasers--;
            }
        }
    }
}

void Player::drawLasers(sf::RenderWindow& window){
    for (auto& l : lasers){
        if (l.isActive()) { 
            window.draw(l.getSprite(), sf::RenderStates::Default); 
        }
    }
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
    else if (key == sf::Keyboard::Space){
        // shoot a laser if possible!
        if ((activeLasers < MAX_LASER_SHOTS) && (lastShot.getElapsedTime().asSeconds() >= LASER_COOLDOWN)){
            lastShot.restart();
            shootLaser();
        }
    }
}

int findUnusedLaser(std::vector<Laser>& lasers){
    for (int i = 0; i < lasers.size(); i++){
        if (lasers[i].isActive() == false){
            return i;
        }
    }

    return -1;
}

void Player::shootLaser(){
    if (activeLasers < MAX_LASER_SHOTS){

        int laserInd = findUnusedLaser(lasers);
        if (laserInd == -1){
            exit(1);
        }

        lasers[laserInd].reset(playerSprite.getPosition(), getDir());
        
        activeLasers++;
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

std::vector<Laser>& Player::getLasers(){ return this->lasers; }
void Player::decreaseActiveLasers(){ activeLasers--; }