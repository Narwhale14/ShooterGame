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

    color = sf::Color(0, 255, 0);

    barBack->setFillColor(sf::Color(64, 64, 64));
    barMain->setFillColor(color);

    dead = false;
    health = 100;
}

HealthBar::~HealthBar() {
    delete barBack;
    delete barMain;
}

void HealthBar::setPosition(float pos_x, float pos_y) {
    barBack->setPosition(pos_x, pos_y);
    barMain->setPosition(pos_x, pos_y);
}

void HealthBar::negateHealth(int damage) {
    if(health - damage >= 0) {
        health -= damage;
    } else if(health < damage) {
        health = 0;
    }

    barMain->setSize(sf::Vector2f(barMain->getSize().x * (health / 100.f), barMain->getSize().y));
}

bool HealthBar::getDead() const {
    return dead;
}

void HealthBar::render(sf::RenderTarget& target) {
    target.draw(*barBack);
    target.draw(*barMain);
}