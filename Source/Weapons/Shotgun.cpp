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
Shotgun::Shotgun(sf::Texture* bTexture, sf::Texture* wTexture){
    range=700;
    fireRate=3; //(range/100); //would not recommend going higher then 40
    //BulletShot.resize(fireRate);
    createSprite(wTexture);
    sprite->setScale({.05,.05});
    sprite->setRotation(90);
    Bullet *temp = new Bullet(range,bTexture);
    //BulletShot=new Bullet(range,bTexture);
    // BulletShot1=new Bullet(range,bTexture);
    // BulletShot2=new Bullet(range,bTexture);
    if(fireRate>0){
        //for(unsigned int i=0;i<fireRate;i++){
            BulletShot.push(temp);
        //}
    }
}
/**
 * @brief Destroy the Pistol:: Pistol object
 * 
 */
Shotgun::~Shotgun() {
    // for(int i=0;i<fireRate;i++){
    //     delete BulletShot[i];
    // }
    // BulletShot.clear();

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
void Shotgun::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, sf::Clock c)
{    
        //if(T.asSeconds()>1){
            for(unsigned int i=0;i<BulletShot.size();i++){
                
                Bullet *move;
                BulletShot.front()->fireBull(mouseLoc,playerLoc);
                move=BulletShot.front();
                BulletShot.pop();
                BulletShot.push(move);
                std::cout << "Bullet: "<< i << " " << BulletShot.front()->getPostion().x << ","<<BulletShot.front()->getPostion().y<<std::endl;
            }
            T=c.getElapsedTime();
            if(BulletShot.size()<fireRate&&T.asSeconds()>1){
                BulletShot.push(temp);
                c.restart();
            }
        //}
        //BulletShot1->fireBull({mouseLoc.x+100,mouseLoc.y+100},playerLoc, firing);
        //firing=BulletShot2->fireBull({mouseLoc.x-100,mouseLoc.y-100},playerLoc, firing);
    //}
}

/**
 * @brief fires the last bullet and shoots no more
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Shotgun::stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc, sf::Clock c)
{
    
            for(unsigned int i=0;i<BulletShot.size();i++){
                
                Bullet *move;
                BulletShot.front()->stopBull(mouseLoc,playerLoc);
                move=BulletShot.front();
                BulletShot.pop();
                BulletShot.push(move);
                std::cout << "Bullet: "<< i << " " << BulletShot.front()->getPostion().x << ","<<BulletShot.front()->getPostion().y<<std::endl;
            }
            T=c.getElapsedTime();
            if(BulletShot.size()<fireRate&&T.asSeconds()>1){
                BulletShot.push(temp);
                c.restart();
            }
        //}
        // BulletShot1->stopBull({mouseLoc.x+100,mouseLoc.y+100},playerLoc, firing);
        // firing=BulletShot2->stopBull({mouseLoc.x-100,mouseLoc.y-100},playerLoc, firing);
    //}
}

/**
 * @brief render the bullets
 * 
 * @param target 
 */
void Shotgun::renderBull(sf::RenderTarget& target)
{
    for(unsigned int i=0;i<BulletShot.size();i++)
        BulletShot.front()->render(target);
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