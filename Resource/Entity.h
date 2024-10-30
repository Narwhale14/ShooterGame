/**
 * @file Entity.h
 * @author Niall Murray
 * @brief Entity class declaration (base class for any moving mob)
 * @date 2024-10-23
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "Mortar.h"
#include "Pistol.h"

class Entity {
    public:
        Entity();
        virtual ~Entity();

        void createSprite(sf::Texture* texture);
        void move(const float& dt, const float dir_x, const float dir_y);

        virtual void render(sf::RenderTarget* target) = 0;
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;

        float movementSpeed;
        float angle;
};

#endif