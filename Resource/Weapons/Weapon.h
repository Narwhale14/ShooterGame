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

        void render(sf::RenderTarget& target);
        void createSprite(sf::Texture* texture);
    protected:
        sf::Texture* texture;
        sf::Sprite* sprite;
        sf::Vector2f origMouse;
        sf::Vector2f origPlayer;

        bool firing;
};

#endif