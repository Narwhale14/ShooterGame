#include "../Resource/Player.h"

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param x initial xpos
 * @param y initial ypos
 * @param texture texture
 */
Player::Player(float x, float y, sf::Texture* texture) {
    this->createSprite(texture);
    this->sprite->setPosition(x, y);
}

/**
 * @brief Destroy the Player:: Player object
 * 
 */
Player::~Player() { 

}

/**
 * @brief Tracks front of player to the cursor
 * 
 * @param mousePos coords of the cursor relative to the window
 */
void Player::pointToCursor(const sf::Vector2f mousePos) {
    float dist_x = mousePos.x - this->sprite->getPosition().x;
    float dist_y = mousePos.y - this->sprite->getPosition().y;

    this->angle = (atan2(dist_y, dist_x)) * 180 / 3.14;
    this->sprite->setRotation(angle - 90);
}