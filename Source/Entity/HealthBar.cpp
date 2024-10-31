/**
 * @file HealthBar.cpp
 * @author Niall Murray
 * @brief Health bar class implementation
 * @date 2024-10-30
 */

#include "../../Resource/Entity/HealthBar.h"

HealthBar::HealthBar(float size_x, float size_y, float pos_x, float pos_y) {
    barBack = new sf::RectangleShape(sf::Vector2f(size_x, size_y / 5));
    barMain = new sf::RectangleShape(sf::Vector2f(size_x, size_y / 5));

    barBack->setOrigin(barBack->getGlobalBounds().width / 2, barBack->getGlobalBounds().height / 2);
    barMain->setOrigin(barBack->getGlobalBounds().width / 2, barBack->getGlobalBounds().height / 2);
    barMain->setScale(0.9f, 0.60f);

    setPosition(pos_x, pos_y);

    barBack->setFillColor(sf::Color(64, 64, 64));
    barMain->setFillColor(sf::Color::Green);

    dead = false;
}

HealthBar::~HealthBar() {
    delete barBack;
    delete barMain;
}

void HealthBar::setPosition(float pos_x, float pos_y) {
    barBack->setPosition(pos_x, pos_y);
    barMain->setPosition(pos_x, pos_y);
}

bool HealthBar::getDead() const {
    return dead;
}

void HealthBar::render(sf::RenderTarget& target) {
    target.draw(*barBack);
    target.draw(*barMain);
}