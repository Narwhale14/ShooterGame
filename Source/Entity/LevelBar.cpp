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
LevelBar::LevelBar(sf::Font& font, float size_x, float size_y, float pos_x, float pos_y) {
    barBack.setSize(sf::Vector2f(size_x, size_y / 5));
    barMain.setSize(sf::Vector2f(size_x, size_y / 5));
    maxMainBarSize = barMain.getSize().x;

    barBack.setOrigin(barBack.getGlobalBounds().width / 2, barBack.getGlobalBounds().height / 2);
    barMain.setOrigin(barBack.getGlobalBounds().width / 2, barBack.getGlobalBounds().height / 2);
    barMain.setScale(0.98f, 0.60f);

    color = sf::Color(0, 255, 0);
    barBack.setFillColor(sf::Color(64, 64, 64));
    barMain.setFillColor(color);

    this->font = font;
    text.setFont(font);
    text.setCharacterSize(barBack.getGlobalBounds().height * 1.25f);

    level = 1;
    text.setString("LVL " + std::to_string(level));

    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    text.setPosition(pos_x, pos_y - text.getGlobalBounds().height - barBack.getSize().y);
    text.setFillColor(sf::Color::White);

    setPosition(pos_x, pos_y);

    xp = 0;
    requiredXpToLevelUp = 25;
    levelRatio = 1.25f;
    levelCap = 15;
}

/**
 * @brief Destroy the Level Bar:: Level Bar object
 * 
 */
LevelBar::~LevelBar() {
    
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
 * @brief Returns the xp amount
 * 
 * @return int 
 */
int LevelBar::getLvl() const {
    return level;
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

    bool leveledUp = false;;
    if(xp >= requiredXpToLevelUp && level != levelCap) {
        level++;
        xp -= requiredXpToLevelUp;
        requiredXpToLevelUp *= levelRatio;

        leveledUp = true;
    }

    text.setString("LVL " + std::to_string(level));
    text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);

    if((xp / static_cast<float>(requiredXpToLevelUp)) <= 1.f)
        barMain.setSize(sf::Vector2f(maxMainBarSize * (xp / static_cast<float>(requiredXpToLevelUp)), barMain.getSize().y));
    else if(level == levelCap)
        barMain.setSize(sf::Vector2f(maxMainBarSize, barMain.getSize().y));

    return leveledUp;
}

/**
 * @brief Sets levelBar position
 * 
 * @param pos_x 
 * @param pos_y 
 */
void LevelBar::setPosition(float pos_x, float pos_y) {
    barBack.setPosition(pos_x, pos_y);
    barMain.setPosition(pos_x, pos_y);
    text.setPosition(pos_x, pos_y - text.getGlobalBounds().height - barBack.getSize().y);
}

/**
 * @brief Renders visual levelbar
 * 
 * @param target 
 */
void LevelBar::render(sf::RenderTarget& target) {
    target.draw(barBack);

    if(xp != 0)
        target.draw(barMain);

    target.draw(text);
}