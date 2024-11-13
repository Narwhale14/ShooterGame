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
Hitbox::Hitbox(sf::Sprite* s, float offset_x, float offset_y, float width, float height, sf::Color color) {
    sprite = s;
    offsetX = offset_x;
    offsetY = offset_y;

    box = new sf::RectangleShape(sf::Vector2f(width, height));
    box->setPosition(sprite->getPosition().x + offset_x, sprite->getPosition().y + offset_y);
    box->setOrigin(box->getGlobalBounds().width / 2, box->getGlobalBounds().height / 2);
    box->setFillColor(sf::Color::Transparent);

    box->setOutlineThickness(1.f);
    box->setOutlineColor(color);
}

/**
 * @brief Destroy the Hitbox:: Hitbox object
 * 
 */
Hitbox::~Hitbox() {
    delete box;
}

/**
 * @brief Checks to see if hitbox collides with another FloatRect
 * 
 * @param rect 
 * @return true 
 * @return false 
 */
bool Hitbox::checkCollision(const sf::FloatRect* rect) {
    return box->getGlobalBounds().intersects(*rect);
}

/**
 * @brief Returns hitbox position
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Hitbox::getPosition() {
    return box->getPosition();
}

/**
 * @brief Returns hitbox global bounds
 * 
 * @return sf::FloatRect 
 */
sf::FloatRect Hitbox::getGlobalBounds() {
    return box->getGlobalBounds();
}

/**
 * @brief Sets hitbox size
 * 
 * @param size 
 */
void Hitbox::setSize(sf::Vector2f size) {
    box->setSize(size);
}

/**
 * @brief Updates by setting hitbox around player as it moves
 * 
 */
void Hitbox::update() {
    box->setPosition(sprite->getPosition().x + offsetX, sprite->getPosition().y + offsetY);
}

/**
 * @brief Draws hitbox
 * 
 * @param target 
 */
void Hitbox::render(sf::RenderTarget& target) {
    target.draw(*box);
}