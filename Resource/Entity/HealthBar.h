/**
 * @file HealthBar class
 * @author Niall Murray
 * @brief Health Bar class declaration
 * @date 2024-10-30
 */

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Tree.h"

class HealthBar {
    public:
        HealthBar(float size_x, float size_y, float pos_x, float pos_y);
        ~HealthBar();

        void setPosition(float pos_x, float pos_y);
        void setHealth(int new_health);

        int getHealth() const;
        int getMaxHealth() const;

        void render(sf::RenderTarget& target);
    private:
        int health;
        int maxHealth;

        sf::RectangleShape barBack;
        sf::RectangleShape barMain;
        float maxMainBarSize;

        sf::Color color;
};

#endif