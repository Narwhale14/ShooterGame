/**
 * @file Pistol.h
 * @author William Wotherspoon
 * @brief pistol declaration class
 * @version 0.1
 * @date 2024-11-05
 */
#ifndef SHOTGUN_H
#define SHOTGUN_H

#include "Lazergun.h"

class Shotgun : public Weapon {
    public:
        Shotgun(std::map<std::string, sf::Texture>& textures);
        ~Shotgun();
        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
        void update(sf::Vector2f playerTrack);
    private:
        int direction;
        int direction1;
        int direction2;
        int direction3;
};

#endif