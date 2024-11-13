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
    fireRate=(range/100);
    createSprite(wTexture);
    sprite->setScale({.05,.05});
    sprite->setRotation(90);
    //Bullet *temp = new Bullet(r,texture);
    BulletShot=new Bullet(range,bTexture);
    BulletShot1=new Bullet(range,bTexture);
    BulletShot2=new Bullet(range,bTexture);
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
Shotgun::~Shotgun() {
    // for(int i=0;i<fireRate;i++){
    //     delete capacity[i];
    // }
    delete BulletShot;
    delete BulletShot1;
    delete BulletShot2;
}

/**
 * @brief fires the bullet out of the pistol
 * 
 * @param mouseLoc location of player mouse
 * @param playerLoc location of player
 */
void Shotgun::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    float adjX=playerLoc.x-mouseLoc.x;
    float adjY=playerLoc.y-mouseLoc.y;
    float length = sqrt((adjX*adjX)+(adjY*adjY));       
    for(int i=0;i<fireRate;i++){
        //firing = capacity[i]->fireBull(mouseLoc,playerLoc, firing);
        BulletShot->fireBull(mouseLoc,playerLoc, firing);
        BulletShot1->fireBull({mouseLoc.x+100,mouseLoc.y+100},playerLoc, firing);
        firing=BulletShot2->fireBull({mouseLoc.x-100,mouseLoc.y-100},playerLoc, firing);
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
void Shotgun::stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
   for(int i=0;i<fireRate;i++){
        BulletShot->stopBull(mouseLoc,playerLoc, firing);
        BulletShot1->stopBull({mouseLoc.x+100,mouseLoc.y+100},playerLoc, firing);
        firing=BulletShot2->stopBull({mouseLoc.x-100,mouseLoc.y-100},playerLoc, firing);
    }
}

/**
 * @brief render the bullets
 * 
 * @param target 
 */
void Shotgun::renderBull(sf::RenderTarget& target)
{
    //capacity[0]->render(target);
    BulletShot->render(target);
    BulletShot1->render(target);
    BulletShot2->render(target);
}

void Shotgun::render(sf::RenderTarget& target)
{
    //capacity[0]->render(target);
    if(sprite)
        target.draw(*sprite);
}

void Shotgun::update(sf::Vector2f playerTrack) {
    sprite->setPosition(playerTrack.x,playerTrack.y);
}