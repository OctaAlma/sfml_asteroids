#include <SFML/Graphics.hpp>
#include "./Laser.hpp"
#include <vector>

#define SHIP_TEXTURE "./resources/ship.png"
#define SHIP_SCALE          0.075

#define MAX_SPEED           450.0f
#define SPEED_INCREASE      5.0f
#define NATURAL_SPEED_DEC   3.0f
#define SPEED_THRESHOLD     3.0f

#define MAX_ANGULAR_SPEED   250.0f
#define ANGULAR_INCREASE    15.0f
#define NATURAL_ANGULAR_DEC 3.0f
#define ANGULAR_THRESHOLD   3.0f

#define MAX_LASER_SHOTS     6

enum Direction{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Player{
private:
    sf::Sprite playerSprite;
    sf::Texture playerTexture;
    bool moving[4];
    bool rotating[2];

    sf::Vector2f pos;
    sf::Vector2f moveVec;
    sf::Vector2f momentumVec;

    float angularSpeed;
    float rotation;

    sf::Clock lastShot;
    sf::Texture laserTexture;
    std::vector<Laser> lasers;
    int activeLasers;
    void shootLaser();

public:
    Player();
    sf::Sprite& getSprite();
    void drawLasers(sf::RenderWindow& window);
    void update(sf::Time delta);
    void updateMovement(sf::Keyboard::Key key, bool pressed);
    sf::Vector2f getPos();
    sf::Vector2f getDir();
};