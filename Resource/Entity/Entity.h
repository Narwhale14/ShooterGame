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

        float getMaxVelocity();
        const sf::Vector2f getPosition();
        const sf::FloatRect& getNextPositionBounds() const;
        float getDistanceTo(sf::Vector2f objPos);
        bool isAlive();

        virtual void setPosition(sf::Vector2f pos);
        void setVelocity(sf::Vector2f new_velocity);

        void stopVelocityX();
        void stopVelocityY();

        void changeSprite(sf::Texture* texture);
        virtual void changeHealth(int incoming);
        void checkCollision(Entity* entity);
        
        void createHealthBar(float size_x, float size_y, float pos_x, float pos_y);

        void move(const float& dt, const float dir_x, const float dir_y);

        virtual void update() = 0;
        virtual void render(sf::RenderTarget& target) = 0;
    protected:
        HealthBar* healthBar;

        sf::Vector2f velocity;
        float maxVelocity;

        float angle;
        float multiplier;
};

#endif