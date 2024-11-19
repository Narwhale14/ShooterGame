/**
 * @file Enemy.h
 * @author Niall Murray
 * @brief Enemy class declarations
 * @date 2024-10-29
 */

#ifndef ENEMY_H
#define ENEMY_H

#include "Player.h"

class Enemy : public Entity {
    public:
        Enemy(std::map<std::string, sf::Texture>& textures, int x, int y);
        virtual ~Enemy();

        int getXPValue() const;
        int getSightDistance() const;
        short unsigned getType() const;

        void track(sf::Vector2f playerPosition);
        void follow(const float& dt, sf::Vector2f playerPosition);

        virtual void render(sf::RenderTarget& target);
        virtual void update();
    private:
        enum type {wolf = 0, bull};
        short unsigned type;

        int xpValue;
        int sightDistance;

        short unsigned generateEnemyType();
};

#endif