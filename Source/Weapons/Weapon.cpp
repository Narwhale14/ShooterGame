/**
 * @file Weapon.cpp
 * @author William Wotherspoon
 * @brief 
 * @version 0.1
 * @date 2024-10-24 
 */
#include "../../Resource/Weapons/Weapon.h"

/**
 * @brief Construct a new Weapon:: Weapon object
 * 
 */
Weapon::Weapon() {
    texture = nullptr;
    sprite = nullptr;
    firing=false;
    origPlayer={0.f,0.f};
    origMouse={0.f,0.f};
}

/**
 * @brief retrieve the firing state
 * 
 * @return true 
 * @return false 
 */
bool Weapon::getFiringStatus() {
    return firing;
}

/**
 * @brief set the firing state
 * 
 * @param status 
 */
void Weapon::setFiringStatus(bool status) {
    firing = status;
}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Weapon::render(sf::RenderTarget* target) {
    if(sprite) {
        target->draw(*sprite);
    }
}

/**
 * @brief Initializes sprite and sets its origin to the center + scales it down to 10%
 * 
 * @param texture a pointer pointing to a texture
 */
void Weapon::createSprite(sf::Texture* texture) {
    this->texture = texture;
    sprite = new sf::Sprite(*this->texture);

    // Sets origin to middle of shape
    sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    sprite->setScale(0.1f, 0.1f);
}

/**
 * @brief Destroy the Entity:: Entity object
 *        Deletes dynamically allocated sprite and texture
 */
Weapon::~Weapon() {
    delete sprite;
}