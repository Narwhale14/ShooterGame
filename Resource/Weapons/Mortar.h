#ifndef MORTAR_H
#define MORTAR_H

#include "Bullet.h"

class Mortar : public Weapon {
    public:
        Mortar(float r = 0, sf::Texture* texture = nullptr);
        ~Mortar();

        void fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc);
    private:
        float range;
};

#endif

//when player press space(fire input) create Singleshot object passing the range, radius and direction.
    //the class default constructor create a circleshape. Then for each game loop move the projectile.