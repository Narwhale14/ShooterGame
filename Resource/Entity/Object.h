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
        Object();
        virtual ~Object();
        
        sf::FloatRect getHitboxBounds() const;
        sf::FloatRect getNextPosBounds() const;
        sf::Color getHitboxColor() const;
        void showHitbox(bool visible);
        
        void createHitbox(sf::Sprite* s, float width, float height, sf::Color color, bool isEntity);

        virtual void createSprite(sf::Texture* texture, float scale);

        virtual void render(sf::RenderTarget& target) = 0;
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        sf::Color color;
        float scale;

        Hitbox* hitbox;
};

#endif