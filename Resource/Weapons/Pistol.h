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
        std::vector<Bullet*> capacity;
    private:
        Bullet *test;
        bool ammoEmpty;
};

#endif