/**
 * @file Pistol.cpp
 * @author William Wotherspoon
 * @brief function definitions for the pistol class
 * @version 0.1
 * @date 2024-11-05
 */
#include "../../Resource/Weapons/Shotgun.h"

/**
 * @brief Construct a new Pistol:: Pistol object
 * 
 * @param r range of the pistol
 * @param texture bullets texture
 */
Shotgun::Shotgun(std::map<std::string, sf::Texture>& textures){
    //important bulletSpeed cannot go to much higher than move speed
    amount=10;
    createSprite(&textures["GLOCK"], 0.05f);
    sprite->setRotation(90);
    bulletT=&textures["BULLET"];
    //BulletShot=new Bullet(range,bTexture);
    // BulletShot1=new Bullet(range,bTexture);
    // BulletShot2=new Bullet(range,bTexture);
    if(amount>0){
        temp = new Bullet(range,bulletT);
        BulletShot.push(temp);
    }
}

/**
 * @brief Destroy the Pistol:: Pistol object
 * 
 */
Shotgun::~Shotgun() {
    for(unsigned int i=0;i<BulletShot.size();i++){
        delete BulletShot.front();
        BulletShot.front()=nullptr;
        BulletShot.pop();
    }

    //delete BulletShot;
    // delete BulletShot1;
    // delete BulletShot2;
}

/**
 * @brief fires the bullet out of the pistol
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Shotgun::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
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
        if(T.asSeconds()>fireRate && BulletShot.size()<amount && BulletShot.back()->getFiringStat()){
            Bullet *newTemp = new Bullet(range,bulletT);
            BulletShot.push(newTemp);
            C.restart();
        }
        //BulletShot1->fireBull({mouseLoc.x+100,mouseLoc.y+100},playerLoc, firing);
        //firing=BulletShot2->fireBull({mouseLoc.x-100,mouseLoc.y-100},playerLoc, firing);
}

/**
 * @brief fires the last bullet and shoots no more
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Shotgun::stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
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
        // BulletShot1->stopBull({mouseLoc.x+100,mouseLoc.y+100},playerLoc, firing);
        // firing=BulletShot2->stopBull({mouseLoc.x-100,mouseLoc.y-100},playerLoc, firing);
}

/**
 * @brief render the bullets
 * 
 * @param target 
 */
void Shotgun::renderBull(sf::RenderTarget& target)
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
    // BulletShot1->render(target);
    // BulletShot2->render(target);
}

void Shotgun::render(sf::RenderTarget& target)
{
    if(sprite)
        target.draw(*sprite);
}

void Shotgun::update(sf::Vector2f playerTrack) {
    sprite->setPosition(playerTrack.x,playerTrack.y);
}