#include "../../Resource/Entity/Player.h"

/**
 * @brief Construct a new Player:: Player object
 * 
 * @param x initial xpos
 * @param y initial ypos
 * @param texture texture
 */
Player::Player(std::map<std::string, sf::Texture>& textures, int x, int y, float s) {
    idle = &textures["PLAYER_NORMAL"];
    aimed = &textures["PLAYER_AIMED"];

    createSprite(idle, s);
    setPosition(sf::Vector2f(x, y));

    createHitbox(sprite, 0.f, 0.f, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Green);
    createHealthBar(50, 50, sprite->getPosition().x, sprite->getPosition().y);

    handheld = new Pistol(textures);
    handheldType = gun;
}

std::vector<Bullet*>& Player::getActiveBullets() {
    return handheld->getBulletList();
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
void Player::updateRotation(const sf::Vector2f mousePos) {
    float dist_x = mousePos.x - sprite->getPosition().x;
    float dist_y = mousePos.y - sprite->getPosition().y;

    angle = ((atan2(dist_y, dist_x)) * 180 / 3.14);

    weaponPos.x = sprite->getPosition().x + (hitbox->getGlobalBounds().width / 1.1f) * cos(angle * 3.14 / 180);
    weaponPos.y = sprite->getPosition().y + (hitbox->getGlobalBounds().height / 1.1f) * sin(angle * 3.14 / 180);
    
    sprite->setRotation(angle - 90);

    handheld->update(weaponPos);
    handheld->rotateWeapon(mousePos);
}

void Player::useHandheld(const sf::Vector2f mousePos) {
    handheld->fire(mousePos, weaponPos);
}

void Player::stopHandheld(const sf::Vector2f mousePos)
{
    handheld->stopFire(mousePos, weaponPos);
}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Player::render(sf::RenderTarget& target) {
    handheld->renderBull(target);

    if(healthBar)
        healthBar->render(target);

    if(handheld)
        handheld->render(target);

    if(sprite)
        target.draw(*sprite);

    if(hitbox)
        hitbox->render(target);
}

/**
 * @brief Updates player and it's sprite
 * 
 */
void Player::update() {
    healthBar->setPosition(hitbox->getPosition().x, hitbox->getPosition().y + (hitbox->getGlobalBounds().height));
    hitbox->update();

    switch(handheldType) {
        case empty:
            changeSprite(idle);
            break;
        case gun:
            changeSprite(aimed);
            break;
        default:
            changeSprite(idle);
            break;
    }
}