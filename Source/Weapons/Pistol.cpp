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
Pistol::Pistol(std::map<std::string, sf::Texture>& textures){
    //important firerate cannot go to much higher than move speed
    amount=30;
    createSprite(&textures["GLOCK"]);
    sprite->setScale({.05,.05});
    sprite->setRotation(90);
    bulletT=&textures["BULLET"];
    if(amount>0){
        temp = new Bullet(range,bulletT);
        BulletShot.push(temp);
    }
}

/**
 * @brief Destroy the Pistol:: Pistol object
 * 
 */
Pistol::~Pistol() {
    for(unsigned int i=0;i<BulletShot.size();i++){
        delete BulletShot.front();
        BulletShot.front()=nullptr;
        BulletShot.pop();
    }
}

/**
 * @brief fires the bullet out of the pistol
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Pistol::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{  
    for(unsigned int x=0;x<bulletSpeed;x++){
        for(unsigned int i=0;i<BulletShot.size();i++){ 
            Bullet *move;
            BulletShot.front()->fireBull(mouseLoc,playerLoc);
            move = BulletShot.front();
            BulletShot.pop();
            if(move->getFiringStat()){
                BulletShot.push(move);
            }else{
                delete move;
            }
        }
    }
    T=C.getElapsedTime();
    if(T.asSeconds()>fireRate && BulletShot.size()<amount){
        Bullet *newTemp = new Bullet(range,bulletT);
        BulletShot.push(newTemp);
        C.restart();
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
    for(unsigned int x=0;x<bulletSpeed;x++){
        for(unsigned int i=0;i<BulletShot.size();i++){ 
            Bullet *move;
            BulletShot.front()->stopBull(mouseLoc,playerLoc);
            move = BulletShot.front();
            BulletShot.pop();
            BulletShot.push(move);
        }
    }
}

/**
 * @brief render the bullets
 * 
 * @param target 
 */
void Pistol::renderBull(sf::RenderTarget& target)
{
    for(unsigned int i=0;i<BulletShot.size();i++){
        if(BulletShot.front()->getFiringStat()){
            BulletShot.front()->render(target);
        }
        Bullet *move;
        move = BulletShot.front();
        BulletShot.pop();
        BulletShot.push(move);
    }
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

void Pistol::increaseFireRate(float percent){
    percent=percent/100;
    bulletSpeed=bulletSpeed+(bulletSpeed*percent);
}