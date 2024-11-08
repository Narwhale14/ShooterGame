/**
 * @file Entity.h
 * @author Niall Murray
 * @brief Entity class declaration (base class for any moving mob)
 * @date 2024-10-23
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "../Weapons/Mortar.h"

class Entity {
    public:
        Entity();
        virtual ~Entity();

        void setScale(float s);
        void setPosition(sf::Vector2f pos);

        void createSprite(sf::Texture* texture);
        void createHitbox(sf::Sprite* s, float offset_x, float offset_y, float width, float height, sf::Color color);
        void createHealthBar(float size_x, float size_y, float pos_x, float pos_y);

        void move(const float& dt, const float dir_x, const float dir_y);

        void update();
        virtual void render(sf::RenderTarget& target) = 0;
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        float scale;

        HealthBar* health;
        Hitbox* hitbox;

        float movementSpeed;
        float angle;
};

#endif