/**
 * @file HealthBar class
 * @author Niall Murray
 * @brief Health Bar class declaration
 * @date 2024-10-30
 */

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include "Hitbox.h"

class HealthBar {
    public:
        HealthBar(float size_x, float size_y, float pos_x, float pos_y);
        ~HealthBar();

        void setPosition(float pos_x, float pos_y);
        void negateHealth(int damage);
        bool getDead() const;

        void render(sf::RenderTarget& target);
    private:
        int health;

        sf::RectangleShape* barBack;
        sf::RectangleShape* barMain;

        sf::Color color;
};

#endif