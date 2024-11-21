/**
 * @file Hitbox.cpp
 * @author Niall Murray
 * @brief Hitbox class init
 * @date 2024-10-30
 */

#include "../../Resource/Entity/Hitbox.h"

/**
 * @brief Construct a new Hitbox:: Hitbox object
 * 
 * @param s sprite that hitbox surrounds
 * @param offset_x x offset
 * @param offset_y y offset
 * @param width width of hitbox
 * @param height height of hitbox
 * @param color hitbox color (green for player, red for damaging, blue for block)
 */
Hitbox::Hitbox(sf::Sprite* s, float width, float height, sf::Color color, bool isEntity) {
    sprite = s;

    if(width > height)
        height = width;
    else
        width = height;

    box.setSize(sf::Vector2f(width, height));
    box.setPosition(sprite->getPosition().x, sprite->getPosition().y);
    box.setOrigin(box.getGlobalBounds().width / 2, box.getGlobalBounds().height / 2);
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineThickness(-1.f);
    box.setOutlineColor(color);

    nextPosition.left = 0.f;
    nextPosition.top = 0.f;
    nextPosition.width = width;
    nextPosition.height = height;

    visible = true;
}
/**
 * @brief Destroy the Hitbox:: Hitbox object
 * 
 */
Hitbox::~Hitbox() {

}

/**
 * @brief Returns hitbox position
 * 
 * @return sf::Vector2f 
 */
const sf::Vector2f Hitbox::getPosition() {
    return box.getPosition();
}

/**
 * @brief Returns hitbox global bounds
 * 
 * @return sf::FloatRect 
 */
const sf::FloatRect Hitbox::getGlobalBounds() {
    return box.getGlobalBounds();
}

/**
 * @brief Returns next pos box bounds
 * 
 * @return sf::FloatRect 
 */
const sf::FloatRect& Hitbox::getNextPosition(const sf::Vector2f& velocity) {
    nextPosition.left = box.getPosition().x - (nextPosition.width / 2.f) + (velocity.x / 50.f);
    nextPosition.top = box.getPosition().y - (nextPosition.height / 2.f) + (velocity.y / 50.f);

    return nextPosition;
}

/**
 * @brief Sets hitbox size
 * 
 * @param size 
 */
void Hitbox::setSize(sf::Vector2f size) {
    box.setSize(size);
}

/**
 * @brief Sets visibility of hitbox
 * 
 * @param visible 
 */
void Hitbox::setVisibility(bool visible) {
    this->visible = visible;
}

/**
 * @brief Updates by setting hitbox around player as it moves
 * 
 */
void Hitbox::update() {
    box.setPosition(sprite->getPosition().x, sprite->getPosition().y);
}

/**
 * @brief Draws hitbox
 * 
 * @param target 
 */
void Hitbox::render(sf::RenderTarget& target) {
    if(visible)
        target.draw(box);
}