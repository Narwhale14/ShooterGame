/**
 * @file Hitbox.h
 * @author Niall Murray
 * @brief Hitbox class declaration
 * @date 2024-10-30
 */

#ifndef HITBOX_H
#define HITBOX_H

#include "LevelBar.h"

class Hitbox {
    public:
        Hitbox(sf::Sprite* s, float width, float height, sf::Color color, bool isEntity);
        ~Hitbox();

        sf::Vector2f getPosition();
        sf::FloatRect getGlobalBounds();

        void setSize(sf::Vector2f size);
        void setVisibility(bool visible);

        void update();
        void updateNextBox(sf::Vector2f velocity);
        void render(sf::RenderTarget& target);
    private:
        sf::RectangleShape box;
        sf::Sprite* sprite;

        sf::RectangleShape nextBox;

        bool visible;
        bool isEntity;
};

#endif