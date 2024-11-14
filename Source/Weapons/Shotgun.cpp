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
    range=700;
     //(range/100); //would not recommend going higher then 40
    amount=10;
    fireRate=5;
    //BulletShot.resize(fireRate);
    createSprite(&textures["GLOCK"]);
    sprite->setScale({.05,.05});
    sprite->setRotation(90);
    bulletT=&textures["BULLET"];
    //BulletShot=new Bullet(range,bTexture);
    // BulletShot1=new Bullet(range,bTexture);
    // BulletShot2=new Bullet(range,bTexture);
    if(fireRate>0){
        //for(unsigned int i=0;i<amount;i++){
            temp = new Bullet(range,&textures["BULLET"]);
            BulletShot.push_back(temp);
        //}
    }
}
/**
 * @brief Destroy the Pistol:: Pistol object
 * 
 */
Shotgun::~Shotgun() {
    for(unsigned int i=0;i<BulletShot.size();i++){
        delete BulletShot[i];
        BulletShot[i]=nullptr;
    }
    delete temp;
    temp = nullptr;
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
        //for(unsigned int x=0;x<fireRate;x++){
            for(unsigned int i=0;i<BulletShot.size();i++){ 
                //if(BulletShot[i]->getFiringStat()){
                BulletShot[i]->fireBull(mouseLoc,playerLoc);
                //}
                std::cout << "Bullet: "<< i << " " << BulletShot[i]->getPostion().x << ","<<BulletShot[i]->getPostion().y<<std::endl;
            }
        //}
            T=c.getElapsedTime();
            // if(T.asSeconds()>2 && amount>1){
            //     amount--;
            //     c.restart();
            // }else if(!BulletShot[BulletShot.size()-1]->getFiringStat()){
            //     amount=BulletShot.size();
            // }
            if(BulletShot.size()<amount && T.asSeconds()>2 && BulletShot[BulletShot.size()-1]->getFiringStat()){
                Bullet *newTemp = new Bullet(range,bulletT);
                BulletShot.push_back(newTemp);
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
        // for(unsigned int x=0;x<fireRate;x++){
        //     for(unsigned int i=0;i<BulletShot.size()-(amount-1);i++){ 
        //         //if(BulletShot[i]->getFiringStat()){
        //         BulletShot[i]->stopBull(mouseLoc,playerLoc);
        //         //}
        //         std::cout << "Bullet: "<< i << " " << BulletShot[i]->getPostion().x << ","<<BulletShot[i]->getPostion().y<<std::endl;
        //     }
        // }
        // T=c.getElapsedTime();
        // if(T.asSeconds()>2 && amount>1){
        //     amount--;
        //     c.restart();
        // }
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
    if(BulletShot[i]->getFiringStat()){
        BulletShot[i]->render(target);
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