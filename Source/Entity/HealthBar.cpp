/**
 * @file HealthBar.cpp
 * @author Niall Murray
 * @brief Health bar class implementation
 * @date 2024-10-30
 */

#include "../../Resource/Entity/HealthBar.h"

HealthBar::HealthBar(float size_x, float size_y) {
    barBack = new sf::RectangleShape();
    barMain = new sf::RectangleShape();

    barBack->setSize(sf::Vector2f(size_x, size_y));
    barMain->setSize(sf::Vector2f(size_x / 2, size_y / 2));

    barBack->setFillColor(sf::Color(128, 128, 128));
    barMain->setFillColor(sf::Color::Green);

    barBack->setOrigin(barBack->getGlobalBounds().width / 2, barBack->getGlobalBounds().height / 2);
    barMain->setOrigin(barMain->getGlobalBounds().width / 2, barMain->getGlobalBounds().height / 2);
}

HealthBar::~HealthBar() {

}

void HealthBar::setPosition(float pos_x, float pos_y) {
    barBack->setPosition(pos_x, pos_y);
}

void HealthBar::update(const float& dt) {

}

void HealthBar::render(sf::RenderTarget& target) {
    target.draw(*barBack);
    target.draw(*barMain);
}