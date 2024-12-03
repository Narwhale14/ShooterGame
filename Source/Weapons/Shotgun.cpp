/**
 * @file Shotgun.cpp
 * @author William Wotherspoon
 * @brief function definitions for the pistol class
 * @version 0.1
 * @date 2024-11-05
 */
#include "../../Resource/Weapons/Shotgun.h"

/**
 * @brief Construct a new Shotgun:: Shotgun object
 * 
 * @param r range of the Shotgun
 * @param texture bullets texture
 */
Shotgun::Shotgun(std::map<std::string, sf::Texture>& textures){
    amount=20;
    createSprite(&textures["SHOTGUN"], 0.05f);
    sprite->setRotation(90);
    bulletT=&textures["PELLET"];
    if(amount>0){
        for(int i=0;i<5;i++){
            temp = new Bullet(range,bulletT);
            BulletShot.push_back(temp);
        }
    }
    srand(time(0));

    dmg = 5;
}

/**
 * @brief Destroy the Shotgun:: Shotgun object
 * 
 */
Shotgun::~Shotgun() {
    for(unsigned int i=0;i<BulletShot.size();i++){
        delete BulletShot.front();
        BulletShot.pop_front();
    }
}

/**
 * @brief fires the bullet out of the Shotgun using the bullet shoot function
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Shotgun::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{    
    direction=rand()%100;
    direction1=rand()%100;
    direction2=rand()%100;
    direction3=rand()%100;

    for(unsigned int x=0;x<7;x++){
        for(unsigned int i=0;i<BulletShot.size();i+=5){ 
            BulletShot[i]->fireBull({mouseLoc.x+direction,mouseLoc.y+direction},playerLoc);
            BulletShot[i+1]->fireBull({mouseLoc.x-direction1,mouseLoc.y-direction1},playerLoc);
            BulletShot[i+2]->fireBull({mouseLoc.x+direction2,mouseLoc.y-direction2},playerLoc);
            BulletShot[i+3]->fireBull({mouseLoc.x-direction3,mouseLoc.y+direction3},playerLoc);
            BulletShot[i+4]->fireBull({mouseLoc.x+direction2,mouseLoc.y+direction3},playerLoc);
            if(!(BulletShot.front()->getFiringStat())){
                for(int z=0;z<5;z++){
                    delete BulletShot.front();
                    BulletShot.pop_front();
                }
            }
        }
    }
    T=C.getElapsedTime();
    if(T.asSeconds()>.4 && BulletShot.size()<amount){
        for(int i=0;i<5;i++){
            Bullet *newTemp = new Bullet(range,bulletT);
            BulletShot.push_back(newTemp);
        }
        C.restart();
    }
}

/**
 * @brief fires the last bullet and shoots no more used to allow for bullet to travel its course before disapearing
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Shotgun::stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    for(unsigned int x=0;x<7;x++){
        for(unsigned int i=0;i<BulletShot.size();i+=5){ 
            BulletShot[i]->fireBull({mouseLoc.x+direction,mouseLoc.y+direction},playerLoc);
            BulletShot[i+1]->fireBull({mouseLoc.x-direction1,mouseLoc.y-direction1},playerLoc);
            BulletShot[i+2]->fireBull({mouseLoc.x+direction2,mouseLoc.y-direction2},playerLoc);
            BulletShot[i+3]->fireBull({mouseLoc.x-direction3,mouseLoc.y+direction3},playerLoc);
            BulletShot[i+4]->fireBull({mouseLoc.x+direction2,mouseLoc.y+direction3},playerLoc);
            if(!(BulletShot.front()->getFiringStat())){
                for(int z=0;z<5;z++){
                    delete BulletShot.front();
                    BulletShot.pop_front();
                }
            }
        }
    }
}

/**
 * @brief updates the weapon to stay with the player
 * 
 * @param playerTrack 
 */
void Shotgun::update(sf::Vector2f playerTrack) {
    sprite->setPosition(playerTrack.x,playerTrack.y);
}