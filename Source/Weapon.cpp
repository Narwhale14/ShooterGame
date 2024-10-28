/**
 * @file Weapon.cpp
 * @author William Wotherspoon
 * @brief 
 * @version 0.1
 * @date 2024-10-24 
 */
#include "../Resource/Weapon.h"

Weapon::Weapon(sf::Texture* texture) {
    this->texture = nullptr;
}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Weapon::render(sf::RenderTarget* target) {
    if(this->sprite) {
        target->draw(*this->sprite);
    }
}

/**
 * @brief Initializes sprite and sets its origin to the center + scales it down to 5%
 * 
 * @param texture a pointer pointing to a texture
 */
void Weapon::createSprite(sf::Texture* texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite(*this->texture);

    // Sets origin to middle of shape
    this->sprite->setScale(0.1f, 0.1f);
    this->sprite->setOrigin(this->sprite->getGlobalBounds().width / 2, this->sprite->getGlobalBounds().height / 2);
}

/**
 * @brief Destroy the Entity:: Entity object
 *        Deletes dynamically allocated sprite and texture
 */
Weapon::~Weapon() {
    delete this->sprite;

    std::cout << "Mortar deleted";
}

void Weapon::update(const float& dt) {

}