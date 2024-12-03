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
    createSprite(texture, 0.1f);
    createHitbox(sprite, sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2, sf::Color::Red);
    hitbox->setSize(sf::Vector2f(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2));
    range=r;
    adjRng=0;
    adjX=0;
    adjY=0;
    origPlayer={0.f,0.f};
    origMouse={0.f,0.f};
    firing=false;
}

/**
 * @brief shoots the projectile from player to mouse
 * 
 * @param mouseLoc location of mouse
 * @param playerLoc location of player
 */
void Bullet::fireBull(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    if(!firing){
        origMouse=mouseLoc;
        origPlayer=playerLoc;
        //std::cout<<"New location\n";
        float distance=0;
        adjX=origPlayer.x-origMouse.x;
        adjY=origPlayer.y-origMouse.y;
        distance=sqrt((adjX*adjX)+(adjY*adjY));
        if(adjX!=0)
            adjX/=distance;
        if(adjY!=0)
            adjY/=distance;
        sprite->setPosition(origPlayer);
        firing = true;
    }
    if(firing){
        sprite->setPosition(sprite->getPosition().x-adjX,sprite->getPosition().y-adjY);
        //std::cout<<"fired\n";
        hitbox->update();
        
        if(range!=adjRng){
            adjRng++;
        }else{
            adjRng=0;
            firing=false;
        }
    }
}

/**
 * @brief finish the display of the last fired bullet and fire no more
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc players location
 * @param fireStatus where the weapon is firing or not
 * @return true 
 * @return false 
 */
void Bullet::stopBull(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    if(!firing){

    }else if(range>adjRng){
        float direct=0;
        adjX=origPlayer.x-origMouse.x;
        adjY=origPlayer.y-origMouse.y;
        direct=sqrt((adjX*adjX)+(adjY*adjY));
        adjX/=direct;
        adjY/=direct;
        sprite->setPosition(sprite->getPosition().x-adjX,sprite->getPosition().y-adjY);
        hitbox->update();
        firing = true;
        adjRng++;
    }else if(range==adjRng){
        adjRng=0;
        firing=false;
    }
}

/**
 * @brief renders the bullet texture to the screen
 * 
 * @param target 
 */
void Bullet::render(sf::RenderTarget& target) {
    if(sprite)
        target.draw(*sprite);

    hitbox->render(target);
}

/**
 * @brief returns the position of the bullet
 * 
 * @return sf::Vector2f 
 */
sf::Vector2f Bullet::getPostion(){
    return sprite->getPosition();
}