/**
 * @file Hitbox.cpp
 * @author Niall Murray
 * @brief Hitbox class init
 * @date 2024-10-30
 */

#include "../../Resource/Entity/Hitbox.h"

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

Hitbox::~Hitbox() {
    delete box;
}

bool Hitbox::checkCollision(const sf::FloatRect* rect) {
    return box->getGlobalBounds().intersects(*rect);
}

sf::Vector2f Hitbox::getPosition() {
    return box->getPosition();
}

sf::FloatRect Hitbox::getGlobalBounds() {
    return box->getGlobalBounds();
}

void Hitbox::setSize(sf::Vector2f size) {
    box->setSize(size);
}

void Hitbox::update() {
    box->setPosition(sprite->getPosition().x + offsetX, sprite->getPosition().y + offsetY);
}

void Hitbox::render(sf::RenderTarget& target) {
    target.draw(*box);
}