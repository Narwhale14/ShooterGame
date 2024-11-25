/**
 * @file Tree.cpp
 * @author Niall Murray
 * @brief Tree class implementation
 * @date 2024-11-21
 */

#include "../../Resource/Entity/Tree.h"

/**
 * @brief Construct a new Tree:: Tree object
 * 
 * @param texture 
 * @param scale 
 */
Tree::Tree(sf::Texture& texture, float scale) {
    createSprite(&texture, scale);
    createHitbox(sprite, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Blue);
}

/**
 * @brief Destroy the Tree:: Tree object
 * 
 */
Tree::~Tree() {

}

/**
 * @brief Sets tree opacity
 * 
 * @param opacity 
 */
void Tree::setOpacity(int opacity) {
    if(opacity < 0 || opacity > 255)
        opacity = 255;

    sprite->setColor(sf::Color(sprite->getColor().r, sprite->getColor().g, sprite->getColor().b, opacity));
}

void Tree::setRotation(int angle) {
    if(angle < 0)
        angle *= -1;
    else if(angle > 360)
        angle %= 360;

    sprite->setRotation(angle);
}

/**
 * @brief Sets position
 * 
 * @param pos 
 */
void Tree::setPosition(const sf::Vector2f& pos) {
    sprite->setPosition(pos);
}

/**
 * @brief Gets position
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Tree::getPosition() const {
    return sprite->getPosition();
}

/**
 * @brief Updates tree
 * 
 */
void Tree::update() {
    hitbox->update();
}

/**
 * @brief Renders tree
 * 
 * @param target 
 */
void Tree::render(sf::RenderTarget& target) {
    if(sprite)
        target.draw(*sprite);

    if(hitbox)
        hitbox->render(target);
}