/**
 * @file Entity.h
 * @author Niall Murray
 * @brief Entity class declaration (base class for any moving mob)
 * @date 2024-10-23
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "../Weapons/Pistol.h"

class Entity {
    public:
        Entity(int scale = 0.075f);
        virtual ~Entity();

        void setScale(float s);
        void setPosition(sf::Vector2f pos);

        void createSprite(sf::Texture* texture);
        void move(const float& dt, const float dir_x, const float dir_y);

        virtual void render(sf::RenderTarget* target) = 0;
        virtual void renderHealth(sf::RenderTarget* target) = 0;
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        float scale;

        //HealthBar* health;

        float movementSpeed;
        float angle;
};

#endif