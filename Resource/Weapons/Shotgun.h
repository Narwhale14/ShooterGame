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
        Shotgun(std::map<std::string, sf::Texture>& textures);
        ~Shotgun();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void renderBull(sf::RenderTarget& target);
        void render(sf::RenderTarget& target);
        void update(sf::Vector2f playerTrack);
    private:
        std::queue<Bullet*> BulletShot;
        Bullet *temp;
        // Bullet *BulletShot1;
        // Bullet *BulletShot2;
};

#endif