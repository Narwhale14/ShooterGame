/**
 * @file Pistol.cpp
 * @author William Wotherspoon
 * @brief function definitions for the pistol class
 * @version 0.1
 * @date 2024-11-05
 */
#include "../../Resource/Weapons/Pistol.h"

/**
 * @brief Construct a new Pistol:: Pistol object
 * 
 * @param r range of the pistol
 * @param texture bullets texture
 */
Pistol::Pistol(float r, sf::Texture* bTexture, sf::Texture* wTexture){
    range=r;
    fireRate=10; //would not recommend going higher then 40
    createSprite(wTexture);
    sprite->setScale({.05,.05});
    sprite->setRotation(90);
    //Bullet *temp = new Bullet(r,texture);
    BulletShot=new Bullet(r,bTexture);
    // if(fireRate>0){
    //     for(int i=0;i<fireRate;i++){
    //         capacity.push_back(temp);
    //     }
    // }else{
    //     fireRate=0;
    // }
}

/**
 * @brief Destroy the Pistol:: Pistol object
 * 
 */
Pistol::~Pistol() {
    // for(int i=0;i<fireRate;i++){
    //     delete capacity[i];
    // }
    delete BulletShot;
}

/**
 * @brief fires the bullet out of the pistol
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Pistol::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    for(int i=0;i<fireRate;i++){
        //firing = capacity[i]->fireBull(mouseLoc,playerLoc, firing);
        firing=BulletShot->fireBull(mouseLoc,playerLoc, firing);
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT"))))
        //     i=fireRate; 
    }
}

/**
 * @brief fires the last bullet and shoots no more
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Pistol::stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
   for(int i=0;i<fireRate;i++){
        firing=BulletShot->stopBull(mouseLoc,playerLoc, firing);
    }
}

/**
 * @brief render the bullets
 * 
 * @param target 
 */
void Pistol::renderBull(sf::RenderTarget& target)
{
    //capacity[0]->render(target);
    BulletShot->render(target);
}

void Pistol::render(sf::RenderTarget& target)
{
    //capacity[0]->render(target);
    if(sprite)
        target.draw(*sprite);
}

void Pistol::update(sf::Vector2f playerTrack) {
    sprite->setPosition(playerTrack.x,playerTrack.y);
}