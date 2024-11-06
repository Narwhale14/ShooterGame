/**
 * @file Pistol.h
 * @author William Wotherspoon
 * @brief pistol declaration class
 * @version 0.1
 * @date 2024-11-05
 */
#ifndef PISTOL_H
#define PISTOL_H

#include "Bullet.h"

class Pistol : public Weapon {
    public:
        Pistol(float r, sf::Texture* texture);
        ~Pistol();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void render(sf::RenderTarget& target);
        //std::vector<Bullet*> capacity;
    private:
        Bullet *BulletShot;
};

#endif