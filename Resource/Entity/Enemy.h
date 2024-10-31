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
        Enemy();
        virtual ~Enemy();

        //virtual void initializeHitbox();

        virtual void render(sf::RenderTarget* target);
    private:
};

#endif