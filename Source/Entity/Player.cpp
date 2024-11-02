#include "../../Resource/Entity/Player.h"

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param x initial xpos
 * @param y initial ypos
 * @param texture texture
 */
Player::Player(std::map<std::string, sf::Texture>* textures, int x, int y, float s) {
    createSprite(&(*textures)["PLAYER_NORMAL"]);
    
    setScale(s);
    setPosition(sf::Vector2f(x, y));

    createHitbox(sprite, 0.f, 0.f, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    createHealthBar(50, 50, sprite->getPosition().x, sprite->getPosition().y);

    //handheld = new Bullet(200.f, &(*textures)["BULLET"]);
    handheld = new Pistol(200.f, &(*textures)["BULLET"]);
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

bool Player::useHandheld(const sf::Vector2f mousePos) {
    //if(!handheld->getFiringStatus()) {
        handheld->fire(mousePos,sprite->getPosition());
    //}
    //std::cout << handheld->getFiringStatus()<<"\n";
    return handheld->getFiringStatus();
}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Player::render(sf::RenderTarget& target) {
    if(handheld->getFiringStatus())
        handheld->render(target);

    if(health)
        health->render(target);

    if(hitbox)
        hitbox->render(target);

    if(sprite)
        target.draw(*sprite);

    //handheld->setFiringStatus(false);
}