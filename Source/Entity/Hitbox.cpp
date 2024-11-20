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

    box.setSize(sf::Vector2f(width, height));
    box.setPosition(sprite->getPosition().x, sprite->getPosition().y);
    box.setOrigin(box.getGlobalBounds().width / 2, box.getGlobalBounds().height / 2);
    box.setFillColor(sf::Color::Transparent);
    box.setOutlineThickness(1.f);
    box.setOutlineColor(color);

    visible = false;
    this->isEntity = isEntity;

    if(this->isEntity) {
        nextBox.setSize(sf::Vector2f(width, height));
        nextBox.setPosition(box.getPosition());
        nextBox.setOrigin(box.getOrigin());
        nextBox.setFillColor(sf::Color::Transparent);
        nextBox.setOutlineThickness(1.f);
        nextBox.setOutlineColor(sf::Color::White);
    }
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
sf::Vector2f Hitbox::getPosition() {
    return box.getPosition();
}

/**
 * @brief Returns hitbox global bounds
 * 
 * @return sf::FloatRect 
 */
sf::FloatRect Hitbox::getGlobalBounds() {
    return box.getGlobalBounds();
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

void Hitbox::updateNextBox(sf::Vector2f velocity) {
    if(isEntity)
        nextBox.setPosition(sprite->getPosition().x + velocity.x, sprite->getPosition().y + velocity.y);
}

/**
 * @brief Draws hitbox
 * 
 * @param target 
 */
void Hitbox::render(sf::RenderTarget& target) {
    if(visible && isEntity)
        target.draw(nextBox);

    if(visible)
        target.draw(box);
}