#include <SFML/Graphics.hpp>

#define SHIP_TEXTURE "./resources/ship.png"

#define MAX_SPEED           650.0f
#define SPEED_INCREASE      20.0f
#define NATURAL_SPEED_DEC   10.0f
#define SPEED_THRESHOLD     10.0f

#define MAX_ANGULAR_SPEED   250.0f
#define ANGULAR_INCREASE    10.0f
#define NATURAL_ANGULAR_DEC 3.0f
#define ANGULAR_THRESHOLD   3.0f

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

public:
    Player();
    sf::Sprite& getSprite();
    void update(sf::Time delta);
    void updateMovement(sf::Keyboard::Key key, bool pressed);
};