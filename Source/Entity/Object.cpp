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
}

/**
 * @brief Returns the hitbox bounds
 * 
 * @return sf::FloatRect 
 */
sf::FloatRect Object::getHitboxBounds() const {
    return hitbox->getGlobalBounds();
}

sf::Color Object::getHitboxColor() const {
    return color;
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
void Object::createHitbox(sf::Sprite* s, float offset_x, float offset_y, float width, float height, sf::Color color) {
    this->color = color;
    hitbox = new Hitbox(s, offset_x, offset_y, width, height, this->color);
}

/**
 * @brief Checks to see if hitbox collides with another FloatRect
 * 
 * @param rect 
 * @return true 
 * @return false 
 */
bool Object::checkCollision(const sf::FloatRect rect) {
    return hitbox->getGlobalBounds().intersects(rect);
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