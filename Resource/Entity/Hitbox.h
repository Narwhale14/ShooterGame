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

        const sf::Vector2f getPosition();
        const sf::FloatRect getGlobalBounds();
        const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

        void setSize(sf::Vector2f size);
        void setVisibility(bool visible);

        void update();
        void render(sf::RenderTarget& target);
    private:
        sf::RectangleShape box;
        sf::Sprite* sprite;

        sf::FloatRect nextPosition;

        bool visible;
};

#endif