/**
 * @file Pistol.cpp
 * @author William Wotherspoon
 * @brief single shot pistol class definitions
 * @version 0.1
 * @date 2024-10-29
 */
#include "../../Resource/Weapons/Bullet.h"

/**
 * @brief Construct a new Pistol:: Pistol object
 * 
 * @param r range of shot
 * @param texture texture of shot
 */
Bullet::Bullet(float r, sf::Texture* texture){
    range=r;
    adjRng=0;
    adjX=0;
    adjY=0;
    origPlayer={0.f,0.f};
    origMouse={0.f,0.f};
    createSprite(texture);
}

Bullet::~Bullet() {

}

/**
 * @brief shoots the projectile from player to mouse
 * 
 * @param mouseLoc location of mouse
 * @param playerLoc location of player
 */
bool Bullet::fireBull(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, bool fireStatus)
{
    if(!fireStatus){
        origMouse=mouseLoc;
        origPlayer=playerLoc;
        //std::cout<<"New location\n";
        float direct=0;
        adjX=origPlayer.x-origMouse.x;
        adjY=origPlayer.y-origMouse.y;
        direct=sqrt((adjX*adjX)+(adjY*adjY));
        adjX/=direct;
        adjY/=direct;
        sprite->setPosition(origPlayer);
    }

    sprite->setPosition(sprite->getPosition().x-adjX,sprite->getPosition().y-adjY);
    fireStatus = true;
    
    if(range!=adjRng){
        adjRng++;
    }else{
        adjRng=0;
        adjX=0;
        adjY=0;
        fireStatus=false;
    }
    return fireStatus;
}

bool Bullet::stopBull(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, bool fireStatus)
{
    if(!fireStatus){
        origMouse=mouseLoc;
        origPlayer=playerLoc;
    }
    if(range>adjRng){
        float direct=0;
        adjX=origPlayer.x-origMouse.x;
        adjY=origPlayer.y-origMouse.y;
        direct=sqrt((adjX*adjX)+(adjY*adjY));
        adjX/=direct;
        adjY/=direct;
        sprite->setPosition(sprite->getPosition().x-adjX,sprite->getPosition().y-adjY);
        fireStatus = true;
        adjRng++;
    }
    if(range==adjRng){
        fireStatus=false;
    }

    return fireStatus;
}

void Bullet::render(sf::RenderTarget& target) {
    if(sprite) {
        target.draw(*sprite);
    }
}

/**
 * @brief Initializes sprite and sets its origin to the center + scales it down to 10%
 * 
 * @param texture a pointer pointing to a texture
 */
void Bullet::createSprite(sf::Texture* texture) {
    this->texture = texture;
    sprite = new sf::Sprite(*this->texture);

    // Sets origin to middle of shape
    sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    sprite->setScale(0.1f, 0.1f);
}