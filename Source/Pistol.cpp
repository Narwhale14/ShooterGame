/**
 * @file Pistol.cpp
 * @author William Wotherspoon
 * @brief single shot pistol class definitions
 * @version 0.1
 * @date 2024-10-29
 */
#include "../Resource/Pistol.h"

/**
 * @brief Construct a new Pistol:: Pistol object
 * 
 * @param r range of shot
 * @param texture texture of shot
 */
Pistol::Pistol(float r, sf::Texture* texture){
    range=r;
    adjRng=0;
    adjX=0;
    adjY=0;
    createSprite(texture);
}

Pistol::~Pistol() {

}

/**
 * @brief shoots the projectile from player to mouse
 * 
 * @param mouseLoc location of mouse
 * @param playerLoc location of player
 */
void Pistol::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    if(!firing){
        origMouse=mouseLoc;
        origPlayer=playerLoc;
        std::cout<<"New location\n";
        float direct=0;
        adjX=origPlayer.x-origMouse.x;
        adjY=origPlayer.y-origMouse.y;
        direct=sqrt((adjX*adjX)+(adjY*adjY));
        adjX/=direct;
        adjY/=direct;
        sprite->setPosition(origPlayer);
    }

    sprite->setPosition(sprite->getPosition().x-adjX,sprite->getPosition().y-adjY);
    firing = true;
    
    if(range!=adjRng){
        adjRng++;
    }else{
        adjRng=0;
        adjX=0;
        adjY=0;
        firing=false;
    }
}