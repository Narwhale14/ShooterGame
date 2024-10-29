#include "../Resource/Player.h"

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param x initial xpos
 * @param y initial ypos
 * @param texture texture
 */
Player::Player(float x, float y, std::map<std::string, sf::Texture>* textures) {
    createSprite(&(*textures)["PLAYER"]);
    sprite->setPosition(x, y);

    handheld = new Mortar(30.f, &(*textures)["EXPLOSION"]);
}

/**
 * @brief Destroy the Player:: Player object
 * 
 */
Player::~Player() { 
    delete handheld;
}

/**
 * @brief Tracks front of player to the cursor
 * 
 * @param mousePos coords of the cursor relative to the window
 */
void Player::pointToCursor(const sf::Vector2f mousePos) {
    float dist_x = mousePos.x - sprite->getPosition().x;
    float dist_y = mousePos.y - sprite->getPosition().y;

    angle = (atan2(dist_y, dist_x)) * 180 / 3.14;
    sprite->setRotation(angle - 90);
}

void Player::useHandheld(const sf::Vector2f mousePos) {
    if(!handheld->getFiringStatus()) {
        handheld->fire(mousePos);
    }
}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Player::render(sf::RenderTarget* target) {
    if(sprite) {
        target->draw(*sprite);
    }
    
    if(handheld->getFiringStatus()) {
        handheld->render(target);
    }

    handheld->setFiringStatus(false);
}