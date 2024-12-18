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
        sf::Color getHitboxColor() const;
        float getScale() const;
        float getDefaultScale() const;
        void showHitbox(bool visible);

        void setScale(float scale);
        
        void createHitbox(sf::Sprite* s, float width, float height, sf::Color color);

        virtual void createSprite(sf::Texture* texture, float scale);

        virtual void render(sf::RenderTarget& target) = 0;
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        sf::Color color;
        
        float scale;
        float defaultScale;

        Hitbox* hitbox;
};

#endif