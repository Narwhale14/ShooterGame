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
    dmg=100;
}

/**
 * @brief returns the deque of bullets
 * 
 * @return std::deque<Bullet*>& 
 */
std::deque<Bullet*>& Weapon::getBulletList() {
    return BulletShot;
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
    for(size_t i=0;i<BulletShot.size();i++){
        BulletShot[i]->render(target);
    }
}

/**
 * @brief Initializes sprite and sets its origin to the center
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
    dmg+=2;
}

/**
 * @brief increase dmg of weapon
 * 
 */
void Weapon::increaseDmg()
{
    dmg++;
}

/**
 * @brief increase bullet speed of weapon
 * 
 */
void Weapon::increaseBullSpeed()
{
    if(bulletSpeed>0 && bulletSpeed<20){
        bulletSpeed=bulletSpeed*1.2;
    }
}

/**
 * @brief increase the firerate of weapons
 * 
 */
void Weapon::increaseFireRate()
{
    if(fireRate>.1){
        fireRate-=.1;
    }
}