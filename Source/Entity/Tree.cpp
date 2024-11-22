/**
 * @file Tree.cpp
 * @author Niall Murray
 * @brief Tree class implementation
 * @date 2024-11-21
 */

#include "../../Resource/Entity/Tree.h"

Tree::Tree(sf::Texture& texture, float size) {
    createSprite(&texture, size);
}

Tree::~Tree() {

}

void Tree::setPosition(sf::Vector2f pos) {
    sprite->setPosition(pos);
}

void Tree::update() {

}

void Tree::render(sf::RenderTarget& target) {
    if(sprite)
        target.draw(*sprite);
}