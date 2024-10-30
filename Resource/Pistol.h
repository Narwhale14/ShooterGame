/**
 * @file Pistol.h
 * @author William Wotherspoon
 * @brief single shot pistol class declaration
 * @version 0.1
 * @date 2024-10-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef PISTOL_H
#define PISTOL_H

#include "Weapon.h"

class Pistol : public Weapon {
    public:
        Pistol(float r = 0, sf::Texture* texture = nullptr);
        ~Pistol();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
    private:
        float range;
        float adjY; //direction for the bullet to travel on Y
        float adjX; //direction for the bullet to travel on X
        float adjRng; //used to calculate when max range has been reached
};

#endif
