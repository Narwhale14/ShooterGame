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

        virtual void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc) = 0;
        virtual void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)=0;
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
        float range=1000;
        unsigned int bulletSpeed=10;
        float fireRate=1;
        float angle;
        int dmg;
        sf::Time T;
        sf::Clock C;
        sf::Texture *bulletT;
        unsigned int amount;

};

#endif