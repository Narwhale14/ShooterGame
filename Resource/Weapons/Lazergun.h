/**
 * @file Pistol.h
 * @author William Wotherspoon
 * @brief pistol declaration class
 * @version 0.1
 * @date 2024-11-05
 */
#ifndef LAZERGUN_H
#define LAZERGUN_H

#include "Pistol.h"

class Lazergun : public Weapon {
    public:
        Lazergun(std::map<std::string, sf::Texture>& textures);
        ~Lazergun();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void update(sf::Vector2f playerTrack);
    private:
};

#endif