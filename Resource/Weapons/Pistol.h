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
#include <queue>

class Pistol : public Weapon {
    public:
        //Pistol(float r, sf::Texture* texture);
        Pistol(std::map<std::string, sf::Texture>& textures);
        ~Pistol();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void renderBull(sf::RenderTarget& target);
        void render(sf::RenderTarget& target);
        void update(sf::Vector2f playerTrack);
        void increaseFireRate(float percent);
        //std::vector<Bullet*> capacity;
    private:
        std::queue<Bullet*> BulletShot;
        Bullet *temp;
};

#endif