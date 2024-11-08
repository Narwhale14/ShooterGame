/**
 * @file Hitbox.h
 * @author Niall Murray
 * @brief Hitbox class declaration
 * @date 2024-10-30
 */

#ifndef HITBOX_H
#define HITBOX_H

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

class Hitbox {
    public:
        Hitbox(sf::Sprite* s, float offset_x, float offset_y, float width, float height, sf::Color color);
        ~Hitbox();

        bool checkCollision(const sf::FloatRect& rect);
        sf::Vector2f getPosition();
        sf::FloatRect getHitboxBounds();
        void setSize(sf::Vector2f size);

        void update();
        void render(sf::RenderTarget& target);
    private:
        sf::RectangleShape* box;
        sf::Sprite* sprite;

        float offsetX;
        float offsetY;
};

#endif