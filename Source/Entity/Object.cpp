/**
 * @file Object.cpp
 * @author Niall Murray
 * @brief Object class implementation file
 * @date 2024-11-14
 */

#include "../../Resource/Entity/Object.h"

/**
 * @brief Construct a new Object:: Object object
 * 
 */
Object::Object() {
    
}

/**
 * @brief Destroy the Object:: Object object
 * 
 */
Object::~Object() {
    delete hitbox;
    delete sprite;
}

/**
 * @brief Returns the hitbox bounds (NOTE: Object might not have a hitbox if it's not an entity or bullet)
 * 
 * @return sf::FloatRect 
 */
sf::FloatRect Object::getHitboxBounds() const {
    return hitbox->getGlobalBounds();
}

/**
 * @brief Returns the color of thie hitbox (type)
 * 
 * @return sf::Color 
 */
sf::Color Object::getHitboxColor() const {
    return color;
}

/**
 * @brief Turns on or off the hitbox
 * 
 * @param visible 
 */
void Object::showHitbox(bool visible) {
    if(hitbox != nullptr)
        hitbox->setVisibility(visible);
}

/**
 * @brief Creates hitbox
 * 
 * @param s sprite for hitbox
 * @param offset_x x offset (pos)
 * @param offset_y y offset (pos)
 * @param width width of hitbox
 * @param height height of hitbox
 */
void Object::createHitbox(sf::Sprite* s, float width, float height, sf::Color color) {
    this->color = color;
    hitbox = new Hitbox(s, width, height, this->color);
}

/**
 * @brief Initializes sprite and sets its origin to the center
 * 
 * @param texture a pointer pointing to a texture
 */
void Object::createSprite(sf::Texture* texture, float scale) {
    this->texture = texture;
    this->scale = scale;
    sprite = new sf::Sprite(*this->texture);

    sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    sprite->setScale(this->scale, this->scale);
}