#include "../../Resource/Weapons/Pistol.h"

Pistol::Pistol(float r, sf::Texture* texture){
    range=r;
    ammo=10;//right now is more so speed then ammo
    ammoEmpty=false;
    //createSprite(texture);
    //Bullet *temp = new Bullet(r,texture);
    test=new Bullet(r,texture);
    // if(ammo>0){
    //     for(int i=0;i<ammo;i++){
    //         capacity.push_back(temp);
    //     }
    // }else{
    //     ammo=0;
    // }
}

Pistol::~Pistol() {
    // for(int i=0;i<ammo;i++){
    //     delete capacity[i];
    // }
    delete test;
}

void Pistol::fire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    for(int i=0;i<ammo;i++){
        //firing = capacity[i]->fireBull(mouseLoc,playerLoc, firing);
        firing=test->fireBull(mouseLoc,playerLoc, firing);
        // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("SHOOT"))))
        //     i=ammo; 
    }
}

void Pistol::stopFire(sf::Vector2f mouseLoc,sf::Vector2f playerLoc)
{
    for(int i=0;i<ammo;i++){
        firing=test->stopBull(mouseLoc,playerLoc, firing);
    }
}

void Pistol::render(sf::RenderTarget& target)
{
    //capacity[0]->render(target);
    test->render(target);
}
