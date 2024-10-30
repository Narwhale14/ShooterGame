/**
 * @file HealthBar class
 * @author Niall Murray
 * @brief Health Bar class declaration
 * @date 2024-10-30
 */

#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <cmath>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class HealthBar {
    public:
        HealthBar(float size_x = 1, float size_y = 1);
        virtual ~HealthBar();

        void setPosition(float pos_x, float pos_y);

        void update(const float& dt);
        void render(sf::RenderTarget& target);
    private:
        int health;

        sf::RectangleShape barBack;
        sf::RectangleShape barMain;
};

#endif