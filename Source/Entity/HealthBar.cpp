/**
 * @file HealthBar.cpp
 * @author Niall Murray
 * @brief Health bar class implementation
 * @date 2024-10-30
 */

#include "../../Resource/Entity/HealthBar.h"

/**
 * @brief Construct a new Health Bar:: Health Bar object
 * 
 * @param size_x x size of healthbar
 * @param size_y y size of healthbar
 * @param pos_x x position of healthbar
 * @param pos_y y position of healthbar
 */
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

    health = 100;
}

/**
 * @brief Destroy the Health Bar:: Health Bar object
 * 
 */
HealthBar::~HealthBar() {
    delete barBack;
    delete barMain;
}

/**
 * @brief Sets healthbar position
 * 
 * @param pos_x 
 * @param pos_y 
 */
void HealthBar::setPosition(float pos_x, float pos_y) {
    barBack->setPosition(pos_x, pos_y);
    barMain->setPosition(pos_x, pos_y);
}

/**
 * @brief Sets health
 * 
 * @param new_health 
 */
void HealthBar::setHealth(int new_health) {
    if(new_health < 0)
        health = 0;
    else
        health = new_health;

    barMain->setSize(sf::Vector2f(barMain->getSize().x * (health / 100.f), barMain->getSize().y));
}

/**
 * @brief Returns health
 * 
 * @return int 
 */
int HealthBar::getHealth() const {
    return health;
}

/**
 * @brief Renders visual healthbar
 * 
 * @param target 
 */
void HealthBar::render(sf::RenderTarget& target) {
    target.draw(*barBack);
    target.draw(*barMain);
}