/**
 * @file Weapon.cpp
 * @author William Wotherspoon
 * @brief 
 * @version 0.1
 * @date 2024-10-24 
 */
#include "../../Resource/Weapons/Weapon.h"

/**
 * @brief Construct a new Weapon:: Weapon object
 * 
 */
Weapon::Weapon() {
    texture = nullptr;
    sprite = nullptr;
    fireRate=1; //the closer to 0 the less time between each shot
    bulletSpeed=6; //when fire rate 1 dont go above 8
    dmg=1;
}

std::deque<Bullet*>& Weapon::getBulletList() {
    return BulletShot;
}

/**
 * @brief retrieve the firing state
 * 
 * @return true 
 * @return false 
 */
bool Weapon::getFiringStatus() {
    return false;
}

/**
 * @brief set the firing state
 * 
 * @param status 
 */
void Weapon::setFiringStatus(bool status) {
    //firing = status;
}

/**
 * @brief Posts sprite to window
 * 
 * @param target 
 */
void Weapon::render(sf::RenderTarget& target) {
    if(sprite)
        target.draw(*sprite);
}

void Weapon::renderBull(sf::RenderTarget& target) {
    for(unsigned int i=0;i<BulletShot.size();i++){
        if(BulletShot[i]->getFiringStat())
            BulletShot[i]->render(target);
    }
}

/**
 * @brief Initializes sprite and sets its origin to the center + scales it down to 10%
 * 
 * @param texture a pointer pointing to a texture
 */
void Weapon::createSprite(sf::Texture* texture, float scale) {
    this->texture = texture;
    this->scale = scale;
    sprite = new sf::Sprite(*this->texture);

    // Sets origin to middle of shape
    sprite->setOrigin(sprite->getGlobalBounds().width / 2, sprite->getGlobalBounds().height / 2);
    sprite->setScale(scale, scale);
}

void Weapon::update(sf::Vector2f playerTrack){

}

void Weapon::rotateWeapon(const sf::Vector2f mousePos){
    float dist_x = mousePos.x - sprite->getPosition().x;
    float dist_y = mousePos.y - sprite->getPosition().y;

    angle = (atan2(dist_y, dist_x)) * 180 / 3.14;
    sprite->setRotation(angle);
}

/**
 * @brief Destroy the Entity:: Entity object
 *        Deletes dynamically allocated sprite and texture
 */
Weapon::~Weapon() {
    delete sprite;
}

/**
 * @brief get the damage of the weapon
 * 
 * @return int weapons damage
 */
int Weapon::getDmg()
{
    return dmg;
}

/**
 * @brief set the weapons damage
 * 
 * @param d new damage value
 */
void Weapon::setDmg(int d)
{
    dmg=d;
}