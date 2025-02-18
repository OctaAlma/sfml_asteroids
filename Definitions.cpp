#include "./Definitions.h"
#include <random>
#include <SFML/Graphics.hpp>

float getRandom(float low, float high){
    return low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(high-low)));
}

void normalize(sf::Vector2f& vec){
    float len = sqrt(vec.x * vec.x + vec.y * vec.y);
    vec.x /= len; 
    vec.y /= len;
}

void snapPosition(sf::Vector2f& pos){
    if (pos.x < LOWER_BOUND_X) { pos.x = UPPER_BOUND_X; }
    else if (pos.x > UPPER_BOUND_X) { pos.x = LOWER_BOUND_X; }

    if (pos.y < LOWER_BOUND_Y) { pos.y = UPPER_BOUND_Y; }
    else if (pos.y > UPPER_BOUND_Y) { pos.y = LOWER_BOUND_Y; }
}

void rotateVec(sf::Vector2f& vec, float angle){
    float sinTheta = std::sin(angle * M_PI / 180.0f);
    float cosTheta =  std::cos(angle * M_PI / 180.0f);
    float x = vec.x;
    float y = vec.y;
    
    vec.x = x * cosTheta + y * sinTheta;
    vec.y = x * sinTheta - y * cosTheta;
}

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
