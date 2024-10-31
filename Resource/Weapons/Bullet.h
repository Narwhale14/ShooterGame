/**
 * @file Bullet.h
 * @author William Wotherspoon
 * @brief single shot pistol class declaration
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef BULLET_H
#define BULLET_H

#include "Weapon.h"

class Bullet : public Weapon {
    public:
        Bullet(float r, sf::Texture* texture);
        ~Bullet();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
    private:
        float range;
        float adjY; //direction for the bullet to travel on Y
        float adjX; //direction for the bullet to travel on X
        float adjRng; //used to calculate when max range has been reached
};

#endif
