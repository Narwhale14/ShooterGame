/**
 * @file Object.h
 * @author Niall Murray
 * @brief Object class declaration (Abstract class)
 * @date 2024-11-14
 */

#ifndef OBJECT_H
#define OBJECT_H

#include "Hitbox.h"

class Object {
    public:
        virtual ~Object();
        
        sf::FloatRect getHitboxBounds();
        unsigned getType() const;
        void setType(unsigned type);
        
        void createHitbox(sf::Sprite* s, float offset_x, float offset_y, float width, float height, sf::Color color);
        bool checkCollision(const sf::FloatRect rect);

        void createSprite(sf::Texture* texture, float scale);
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        float scale;

        Hitbox* hitbox;

        enum type {invalid = 0, player, block, enemy, bullet};
        unsigned type;

        Object();
};

#endif