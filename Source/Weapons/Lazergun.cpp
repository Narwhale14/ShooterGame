/**
 * @file Lazergun.cpp
 * @author William Wotherspoon
 * @brief function definitions for the Lazergun class
 * @version 0.1
 * @date 2024-11-05
 */
#include "../../Resource/Weapons/Lazergun.h"

/**
 * @brief Construct a new Lazergun:: Lazergun object
 * 
 * @param r range of the Lazergun
 * @param texture bullets texture
 */
Lazergun::Lazergun(std::map<std::string, sf::Texture>& textures){
    amount=100;
    createSprite(&textures["GLOCK"], 0.05);
    sprite->setRotation(90);
    bulletT=&textures["LAZERBULL"];
    if(amount>0){
            temp = new Bullet(range,bulletT);
            BulletShot.push_back(temp);
    }
}

/**
 * @brief Destroy the Lazergun:: Lazergun object
 * 
 */
Lazergun::~Lazergun() {
    for(unsigned int i=0;i<BulletShot.size();i++){
        // BulletShot.front()=nullptr;
        // BulletShot.pop();
        delete BulletShot[i];
    }
}

/**
 * @brief fires the bullet out of the Lazergun
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Lazergun::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{  
    for(unsigned int x=0;x<13;x++){
        for(unsigned int i=0;i<BulletShot.size();i++){ 
            BulletShot[i]->fireBull(mouseLoc,playerLoc);
            if(!(BulletShot.front()->getFiringStat())){
                delete BulletShot.front();
                BulletShot.pop_front();
            }
        }
    }
    T=C.getElapsedTime();
    if(T.asSeconds()>.000001 && BulletShot.size()<amount){
        Bullet *newTemp = new Bullet(range,bulletT);
        BulletShot.push_back(newTemp);
        C.restart();
    }
}

/**
 * @brief fires the last bullet and shoots no more
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Lazergun::stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    for(unsigned int x=0;x<13;x++){
        for(unsigned int i=0;i<BulletShot.size();i++){ 
            BulletShot[i]->stopBull(mouseLoc,playerLoc);
            if(!(BulletShot.front()->getFiringStat())){
                BulletShot.pop_front();
            }
        }
    }
}


void Lazergun::update(sf::Vector2f playerTrack) {
    sprite->setPosition(playerTrack.x,playerTrack.y);
}