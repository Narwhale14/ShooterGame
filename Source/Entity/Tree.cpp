/**
 * @file Tree.cpp
 * @author Niall Murray
 * @brief Tree class implementation
 * @date 2024-11-21
 */

#include "../../Resource/Entity/Tree.h"

Tree::Tree(sf::Texture& texture, float scale) {
    createSprite(&texture, scale);
    createHitbox(sprite, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Blue);
}

Tree::~Tree() {

}

void Tree::setPosition(sf::Vector2f pos) {
    sprite->setPosition(pos);
    
}

sf::Vector2f Tree::getPosition() const {
    return sprite->getPosition();
}

void Tree::update() {
    hitbox->update();
}

void Tree::render(sf::RenderTarget& target) {
    if(sprite)
        target.draw(*sprite);

    if(hitbox)
        hitbox->render(target);
}