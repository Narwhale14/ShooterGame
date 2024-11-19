/**
 * @file LevelBar.cpp
 * @author Niall Murray
 * @brief LevelBar class implementation
 * @date 2024-11-18
 */

#include "../../Resource/Entity/LevelBar.h"

/**
 * @brief Construct a new Level Bar:: Level Bar object
 * 
 * @param size_x 
 * @param size_y 
 * @param pos_x 
 * @param pos_y 
 */
LevelBar::LevelBar(float size_x, float size_y, float pos_x, float pos_y) {
    barBack = new sf::RectangleShape(sf::Vector2f(size_x, size_y / 5));
    barMain = new sf::RectangleShape(sf::Vector2f(size_x, size_y / 5));
    maxMainBarSize = barMain->getSize().x;

    barBack->setOrigin(barBack->getGlobalBounds().width / 2, barBack->getGlobalBounds().height / 2);
    barMain->setOrigin(barBack->getGlobalBounds().width / 2, barBack->getGlobalBounds().height / 2);
    barMain->setScale(0.98f, 0.60f);

    setPosition(pos_x, pos_y);

    color = sf::Color(0, 255, 0);

    barBack->setFillColor(sf::Color(64, 64, 64));
    barMain->setFillColor(color);

    level = 0;
    xp = 0;

    requiredXpToLevelUp = 15;
    levelRatio = 1.5f;
}

/**
 * @brief Destroy the Level Bar:: Level Bar object
 * 
 */
LevelBar::~LevelBar() {
    delete barBack;
    delete barMain;
}

/**
 * @brief Returns the xp amount
 * 
 * @return int 
 */
int LevelBar::getXp() const {
    return xp;
}

/**
 * @brief Adds xp and returns whether player levels up
 * 
 * @param incoming 
 * @return true 
 * @return false 
 */
bool LevelBar::addXp(int incoming) {
    xp += incoming;

    if(xp > requiredXpToLevelUp) {
        xp -= requiredXpToLevelUp;
        requiredXpToLevelUp *= levelRatio;
        level++;

        barMain->setSize(sf::Vector2f(maxMainBarSize * (xp / static_cast<float>(requiredXpToLevelUp)), barMain->getSize().y));
        return true;
    }

    barMain->setSize(sf::Vector2f(maxMainBarSize * (xp / static_cast<float>(requiredXpToLevelUp)), barMain->getSize().y));
    return false;
}

/**
 * @brief Sets levelBar position
 * 
 * @param pos_x 
 * @param pos_y 
 */
void LevelBar::setPosition(float pos_x, float pos_y) {
    barBack->setPosition(pos_x, pos_y);
    barMain->setPosition(barBack->getPosition());
}

/**
 * @brief Renders visual levelbar
 * 
 * @param target 
 */
void LevelBar::render(sf::RenderTarget& target) {
    target.draw(*barBack);

    if(xp != 0)
        target.draw(*barMain);
}