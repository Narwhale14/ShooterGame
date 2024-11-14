/**
 * @file Pistol.h
 * @author William Wotherspoon
 * @brief pistol declaration class
 * @version 0.1
 * @date 2024-11-05
 */
#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Pistol.h"
#include <queue>

class Shotgun : public Weapon {
    public:
        Shotgun(sf::Texture* bTexture, sf::Texture* wTexture);
        ~Shotgun();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, sf::Clock c);
        void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, sf::Clock c);
        void renderBull(sf::RenderTarget& target);
        void render(sf::RenderTarget& target);
        void update(sf::Vector2f playerTrack);
    private:
        std::queue<Bullet*> BulletShot;
        sf::Time T;
        Bullet *temp;
        // Bullet *BulletShot1;
        // Bullet *BulletShot2;
};

#endif