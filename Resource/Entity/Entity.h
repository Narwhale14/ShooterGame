/**
 * @file Entity.h
 * @author Niall Murray
 * @brief Entity class declaration (base class for any moving mob)
 * @date 2024-10-23
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "../Weapons/Mortar.h"

class Entity : public Object {
    public:
        Entity();
        virtual ~Entity();

        float getMovementSpeed();
        sf::Vector2f getPosition();
        sf::FloatRect getHitboxBounds();
        bool isAlive();

        void negateHealth(int damage);
        void setPosition(sf::Vector2f pos);

        void changeSprite(sf::Texture* texture);
        
        void createHealthBar(float size_x, float size_y, float pos_x, float pos_y);

        void move(const float& dt, const float dir_x, const float dir_y);

        virtual void update() = 0;
        virtual void render(sf::RenderTarget& target) = 0;
    protected:
        HealthBar* health;

        float movementSpeed;
        float angle;
};

#endif