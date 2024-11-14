/**
 * @file weapon.h
 * @author William Wotherspoon
 * @brief Weapon class declaration for that will be used to create the games weapons
 * @version 0.1
 * @date 2024-10-24
 */

#ifndef WEAPON_H
#define WEAPON_H

#include "../Entity/HealthBar.h"

class Weapon{
    public:
        Weapon();
        virtual ~Weapon();

        bool getFiringStatus();
        void setFiringStatus(bool status);

        virtual void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, sf::Clock c) = 0;
        virtual void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, sf::Clock c)=0;
        virtual void render(sf::RenderTarget& target);
        virtual void renderBull(sf::RenderTarget& target);
        void createSprite(sf::Texture* texture);
        virtual void update(sf::Vector2f playerTrack);
        virtual void rotateWeapon(const sf::Vector2f mousePos);
        int getDmg();
        void setDmg(int d);
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        float range;
        unsigned int fireRate;
        float angle;
        int dmg;
};

#endif